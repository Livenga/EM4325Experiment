namespace rr.Uhf;

using System.Collections.Generic;

public delegate void UhfReceivedTags(IUhf reader, IEnumerable<rr.Uhf.Tag> tags);
