#include <pmdsky.h>
#include <cot.h>

typedef struct
{
  int kind;
  short song_id;
  short volume;
  short duration;
  short pan;
} audio_command_t;

audio_command_t g_pending_command = {0};

void (*send_audio_command)(audio_command_t *command) = 0x02018c44;

__attribute__((noinline)) void poll_audio_command(audio_command_t *out_command)
{
  // this functions is hooked from the emulator side
  // and will write the audio command to *out_command

  COT_LOGFMT("AudioEmulator", "poll_audio_command(%x)", out_command);
}

__attribute__((used)) void flush_audio_commands(void)
{
  poll_audio_command(&g_pending_command);

  while (g_pending_command.kind != 0)
  {
    COT_LOGFMT("AudioEmulator", "send_audio_command(%d)", g_pending_command.kind);
    send_audio_command(&g_pending_command);
    g_pending_command.kind = 0;
    poll_audio_command(&g_pending_command);
  }
}
