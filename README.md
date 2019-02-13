# ardurandom

## about
This is a *random* project idea I had (possibly for my English blog project...): using an Arduino as a true hardware random number generator! It touches on basic hardware, statistics, and systems programming...pretty much exactly the sort of project that would interest me. I haven't really started, but I envision the project as consisting of:

- On the Arduino side:
  - Some array of sensors to obtain random environmental data
  - A software entropy pool based on these data
  - A uniform random number generator
- On the Linux side:
  - A kernel module presenting the Arudino serial interface as a regular device file like `/dev/urandom`

Now that I'm a second-semester senior, I can probably actually devote time to this! I'm putting this up on Github now as a reminder to myself and to pressure myself into actually starting. I'll probably license under GPL if this actually gets anywhere, but that's looking too far into the future.

Actually, now that I think about it, maybe this would be more suitable as a Raspberry Pi project...then again, I suppose with an Arduino, I could make a portable "true random number generator" for any Linux computer. I could even 3D print a nice little case for the apparatus! This is getting slightly out of hand.

