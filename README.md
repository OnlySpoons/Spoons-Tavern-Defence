Spoons: Tavern Defence

Change Log 01/05/2021 - Thomas
- Replaced SE_LOAD and LISTENER macros with actual function calls

Change Log 30/04/2021 - Thomas
- Updated SoundEffectPlayer's destructor to correctly delete its buffer

Change Log 29/04/2021 - Thomas
- Hotfix: made audio filepaths relative

Change Log 29/04/2021 - Thomas
- Fixed heap corruption error, was caused by an uninitialised \_format variable in the MusicBuffer constructor

Change Log 29/04/2021 - Thomas
- Fixed char exception, was casued by using incorrect file type
  - Music files must be .wav
  - Sound effects must be .ogg
- Refactored implementation and renamed classes to more accurately reflect what they do
  - SoundDevice
  - SoundEffectLibrary
  - SoundEffectPlayer
  - MusicBuffer
- WARNING: COMMIT NOT STABLE, HEAP CORRUPTION ERROR ON SHUTDOWN

Change Log 28/04/2021 - Thomas
- Audio branch created and initial commit made
- Implemented four classes to handle sound loading and output
  - SoundDevice
  - SoundBuffer
  - MusicBuffer
  - SoundSource
- WARNING: COMMIT NOT STABLE, HARD CRASHES WITH CHAR EXCEPTION
