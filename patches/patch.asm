.nds
.include "symbols.asm"

.open "overlay36.bin", overlay36_start
   .org overlay36_start+0x36F70
       bl 0x0204fd04
       bl flush_audio_commands
       b 0x022e9770
.close

.open "overlay11.bin", overlay11_start
   .org 0x022e976c
       b overlay36_start+0x36F70
.close
