# PS4HEN v2.2.0 BETA

## Features
#### Currently Supported Firmwares
- Firmwares
  - FW 5.05 / 5.07
  - FW 6.72
  - FW 7.00 / 7.01 / 7.02
  - FW 7.50 / 7.51 / 7.55
  - FW 8.00 / 8.01 / 8.03
  - FW 8.50 / 8.52
  - FW 9.00
  - FW 9.03 / 9.04
  - FW 9.50 / 9.51 / 9.60
  - FW 10.00 / 10.01
  - FW 10.50 / 10.70 / 10.71
  - FW 11.00 / 11.02
  - FW 11.50 / 11.52
  - FW 12.00 / 12.02
  - FW 12.50 / 12.52
- Homebrew Enabler
- [Plugins System](https://github.com/Scene-Collective/ps4-hen-plugins)
  - Plugins are bundled into HEN, the `hen.bin` in this repository has plugins as of [latest](https://github.com/Scene-Collective/ps4-hen-plugins/releases/latest) tag.
  - Patches ShellUI to allow more features.
    - Features:
      - More details at [`plugin_mono`](https://github.com/Scene-Collective/ps4-hen-plugins/blob/main/.github/README.md#plugin_mono) page
  - Load PRX into `ScePartyDaemon`
    - (Starts kernel log server on port 3232, based on [klogsrv](https://github.com/ps5-payload-dev/klogsrv))
    - (Starts FTP server on port 2121, based on [ftpsrv](https://github.com/ps5-payload-dev/ftpsrv))
      - **Note: No SELF decryption yet.**
  - Load PRX into retail apps (on startup in CRT `_init_env`) (You can make your own, the bundled one only prints to TTY for now)
- Jailbreak
- Sandbox Escape
- Debug Settings
- External HDD Support
- VR Support
- Remote Package Install
- Rest Mode Support
- External HDD Format Support
- Bypass Firmware Checks
- Debug Trophies Support
- sys_dynlib_dlsym Patch
- UART Enabler
- Never Disable Screenshot
- Remote Play Enabler
- Disable ASLR

## Building

Instructions provided are for Debian based systems. (Tested on Ubuntu)

Install [ps4-payload-sdk](https://github.com/Scene-Collective/ps4-payload-sdk):

```sh
git clone https://github.com/Scene-Collective/ps4-payload-sdk.git
sudo ./install.sh
```

Clone the repository:

```sh
git clone https://github.com/Scene-Collective/ps4-hen.git
```

Compile the payload:

```sh
./build.sh
```

## Contributors
Massive credits to the following:
- [qwertyoruiopz](https://twitter.com/qwertyoruiopz)
- [Specter](https://twitter.com/SpecterDev) 
- [flat_z](https://twitter.com/flat_z)
- [idc](https://twitter.com/3226_2143)
- [Joonie](https://github.com/Joonie86/)
- [Vortex](https://github.com/xvortex)
- [zecoxao](https://twitter.com/notnotzecoxao)
- [SiSTRo](https://github.com/SiSTR0)
- [SocraticBliss](https://twitter.com/SocraticBliss)
- [ChendoChap](https://github.com/ChendoChap)
- [Biorn1950](https://github.com/Biorn1950)
- [Al-Azif](https://github.com/Al-Azif)
- Anonymous
- illusiony

## Helped With Porting
Massive Thanks to the following:
- [BestPig](https://twitter.com/BestPig)
- [LM](https://twitter.com/LightningMods)
- [Al-Azif](https://twitter.com/_AlAzif)
- [zecoxao](https://twitter.com/notnotzecoxao)
