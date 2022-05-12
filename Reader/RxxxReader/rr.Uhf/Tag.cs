namespace rr.Uhf;

using System;


/// <summary></summary>
public sealed class Tag {
  /// <summary></summary>
  public string? Tid { set; get; } = null;

  /// <summary></summary>
  public ushort AntennaId { set; get; } = 1;

  /// <summary></summary>
  public ushort? Crc { set; get; } = null;

  /// <summary></summary>
  public ushort? PcBits { set; get; } = null;

  /// <summary></summary>
  public string Epc { set; get; } = string.Empty;

  /// <summary></summary>
  public double? PhaseAngle { set; get; } = null;

  /// <summary></summary>
  public double? PeakRssi { set; get; } = null;

  /// <summary></summary>
  public DateTime ReceivedAt { set; get; } = DateTime.Now;
}
