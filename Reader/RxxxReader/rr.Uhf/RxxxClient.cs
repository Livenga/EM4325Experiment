namespace rr.Uhf;

using Impinj.OctaneSdk;
using System;
using System.Threading;
using System.Threading.Tasks;


/// <summary></summary>
public class RxxxClient : IUhf {
  /// <summary></summary>
  public bool IsConnected => _client.IsConnected;

  private readonly ImpinjReader _client;
  private readonly string _host;
  private readonly int _port;

  private Settings? settings = null;


  /// <summary></summary>
  public event UhfReceivedTags? ReceivedTags = null;


  /// <summary></summary>
  public RxxxClient(
      string host,
      int    port) {
    _client = new ImpinjReader();
    _host   = host;
    _port   = port;

    _client.ConnectAsyncComplete += OnImpinjReaderConnectAsyncComplete;
    _client.TagOpComplete += OnImpinjTagOpComplete;
    _client.TagsReported += OnImpinjReaderTagsReported;
  }

  private CancellationTokenSource? ctsOpenAsync = null;

  /// <summary></summary>
  public async Task<bool> OpenAsync() {
    if(_client.IsConnected) {
      return true;
    }

    try {
      using(ctsOpenAsync = new CancellationTokenSource()) {
        _client.ConnectAsync(address: _host, port: _port, useTLS: false);
        await Task.Delay(-1, ctsOpenAsync.Token);
      }
    } catch(TaskCanceledException) {
      return true;
    } catch(Exception except) {
      Console.Error.WriteLine($"{except.GetType().Name} {except.Message}");
      Console.Error.WriteLine(except.StackTrace);
    }

    return false;
  }

  /// <summary></summary>
  public void StartInventory() {
    if(! IsConnected)
      return;

    if(settings != null) {
      settings.Report.IncludeAntennaPortNumber = true;
      settings.Report.IncludeCrc               = true;
      settings.Report.IncludePcBits            = true;
      settings.Report.IncludePhaseAngle        = true;
      settings.Report.IncludeFastId            = true;
      settings.Report.IncludePeakRssi          = true;
      settings.Report.Mode = ReportMode.Individual;

      settings.Antennas.DisableAll();

      var ant = settings.Antennas.GetAntenna(1);
      ant.TxPowerInDbm = 24d;
      ant.IsEnabled    = true;

      _client.ApplySettings(settings);
    }

    _client.Start();
  }

  /// <summary></summary>
  public void StopInventory() {
    if(! IsConnected) {
      return;
    }

    _client.Stop();
  }


  private CancellationTokenSource? ctsReadAsync = null;

  /// <summary></summary>
  public async Task ReadAsync(rr.Uhf.TargetTag targetTag) {
    if(ctsReadAsync != null) {
      throw new Exception();
    }
    _client.DeleteAllOpSequences();

    var seq = new TagOpSequence();
    seq.Id = 1234;
    seq.AntennaId = 1;
    seq.SequenceStopTrigger = SequenceTriggerType.None;

    var target = new Impinj.OctaneSdk.TargetTag();
    target.MemoryBank = targetTag.MemoryBank switch {
      rr.Uhf.MemoryBank.Reserved => Impinj.OctaneSdk.MemoryBank.Reserved,
      rr.Uhf.MemoryBank.Epc      => Impinj.OctaneSdk.MemoryBank.Epc,
      rr.Uhf.MemoryBank.Tid      => Impinj.OctaneSdk.MemoryBank.Tid,
      rr.Uhf.MemoryBank.User     => Impinj.OctaneSdk.MemoryBank.User,
      _ => throw new Exception(),
    };
    target.BitPointer = targetTag.Offset;
    target.Data       = targetTag.Data;
    target.Mask       = string.IsNullOrEmpty(targetTag.Mask)
      ? string.Join(string.Empty, Enumerable.Range(0, targetTag.Data.Length).Select(_ => "F").ToArray())
      : targetTag.Mask;

    seq.TargetTag = target;

    var readOp = new TagReadOp() {
      Id             = 1235,
      MemoryBank     = Impinj.OctaneSdk.MemoryBank.Tid,
      AccessPassword = TagData.FromHexString("00000000"),
      WordCount      = 6,
      WordPointer    = 0 };

    seq.Ops.Add(readOp);
    _client.AddOpSequence(seq);

    using(ctsReadAsync = new CancellationTokenSource()) {
      await Task.Delay(5000, ctsReadAsync.Token);
    }
    ctsReadAsync = null;
  }

  /// <summary></summary>
  public void Dispose() {
    if(_client.IsConnected) {
      try {
        _client.Disconnect();
      } catch { }
    }
  }


  /// <summary></summary>
  private void OnImpinjReaderConnectAsyncComplete(
      ImpinjReader reader,
      ConnectAsyncResult result,
      string message) {
    if(result == ConnectAsyncResult.Success) {
      settings = reader.QueryDefaultSettings();
    } else {
      Console.Error.WriteLine($"{result} {message}");
    }

    ctsOpenAsync?.Cancel();
  }

  /// <summary></summary>
  private void OnImpinjTagOpComplete(
      ImpinjReader reader,
      TagOpReport report) {
    foreach(var result in report.Results) {
      switch(result) {
        case TagReadOpResult _result:
          if(_result.SequenceId == 1234 && _result.OpId == 1235) {
            ctsReadAsync?.Cancel();
          }
          break;

        case TagWriteOpResult _result:
          break;
      }
    }
  }

  /// <summary></summary>
  private void OnImpinjReaderTagsReported(
      ImpinjReader reader,
      TagReport report) {
    var n = DateTime.Now;
    var tags = report.Tags.Select(tag => new rr.Uhf.Tag() {
        Tid        = tag.Tid.ToHexString(),
        AntennaId  = tag.AntennaPortNumber,
        Crc        = tag.Crc,
        PcBits     = tag.PcBits,
        Epc        = tag.Epc.ToHexString(),
        PhaseAngle = tag.PhaseAngleInRadians,
        PeakRssi   = tag.PeakRssiInDbm,
        ReceivedAt = n });

    ReceivedTags?.Invoke(this, tags);
  }

  /// <summary></summary>
  private rr.Uhf.Tag ReportTagToUhfTag(Tag tag) => new rr.Uhf.Tag() {
  };
}
