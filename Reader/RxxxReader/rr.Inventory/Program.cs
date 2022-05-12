using rr.Uhf;


if(args.Length == 0) {
  return;
}

using(IUhf reader = new RxxxClient(
      host: args[0],
      port: 5084)) {
  reader.ReceivedTags += OnReceivedTags;

  await reader.OpenAsync();
  reader.StartInventory();

  Console.ReadLine();
  await Task.Delay(500);

  reader.StopInventory();
}


/// <summary></summary>
static void OnReceivedTags(
    rr.Uhf.IUhf reader,
    IEnumerable<rr.Uhf.Tag> tags) {
  foreach(var tag in tags) {
    Console.Error.WriteLine($"{tag.AntennaId} {tag.Tid ?? "_null"} {tag.PhaseAngle:f2} {tag.PeakRssi:f2}");
    Console.Error.WriteLine($"\t{tag.Crc:X4} {tag.PcBits:X4} {tag.Epc}");
    if(tag.Tid?.Contains("E280B044") ?? false) {
      var hexPressure = tag.Epc.Substring(tag.Epc.Length - 8, 8);
      UInt16 lsb = System.Convert.ToUInt16(hexPressure.Substring(4, 4), 16),
             msb = System.Convert.ToUInt16(hexPressure.Substring(0, 4), 16);

      var pressure = BitConverter.UInt32BitsToSingle(((UInt32)msb << 16) | lsb);
      Console.Error.WriteLine($"\t* Pressure {pressure:f3} [kPa]");
    }
    Console.Error.WriteLine();
  }
}
