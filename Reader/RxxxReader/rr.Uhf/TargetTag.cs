namespace rr.Uhf;

/// <summary></summary>
public class TargetTag {
  /// <summary></summary>
  public MemoryBank MemoryBank { set; get; } = MemoryBank.Epc;

  /// <summary></summary>
  public ushort Offset { set; get; } = 0;

  /// <summary></summary>
  public string Data = string.Empty;

  /// <summary></summary>
  public string Mask = string.Empty;
}
