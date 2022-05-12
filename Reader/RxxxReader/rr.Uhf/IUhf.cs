namespace rr.Uhf;

using System;
using System.Threading.Tasks;


/// <summary></summary>
public interface IUhf : IDisposable {
  /// <summary></summary>
  event UhfReceivedTags? ReceivedTags;


  /// <summary></summary>
  Task<bool> OpenAsync();

  /// <summary></summary>
  void StartInventory();

  /// <summary></summary>
  void StopInventory();
}
