This is a simple command line tool for converting `.wav` files into binary stream data for playback on the PC Engine in DDA mode. The output is a `.bin` file of the same name encoded for 5-bit 6992.1875Hz playback. The playback frequency was chosen based on the fastest available rate of an internal timer. This rate is the cpu clock of 7.16mHz divided by 1024. 

Supports 8, 16, and 32 bit .wav files. 24 bit seems to be the only other typical/popular bit depth, but the spec says anything between 9 and 31 bit are signed integers. 8 bit is unsigned and 32 bit is float. C doesn't natively support 3 byte (24 bit) signed integers, but this could probably easily be solved for.

Some links that may be helpful:
- [How to handle asymmetry of WAV data](https://gist.github.com/endolith/e8597a58bcd11a6462f33fa8eb75c43d)
- [24 bits WAV into FLOAT](https://www.kvraudio.com/forum/viewtopic.php?p=808090&sid=6e73b0b1e8a3e6b0d1be668bdd7b57f8#p808090)
- [WAV File Header spec](https://docs.fileformat.com/audio/wav/)
