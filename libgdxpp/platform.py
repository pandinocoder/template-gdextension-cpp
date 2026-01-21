import platform

from enum import Enum

class Platform(Enum):
    Android = 'android'
    iOS = 'ios'
    Linux = 'linux'
    MacOS = 'macos'
    Web = 'web'
    Windows = 'windows'

    @staticmethod
    def get_current() -> Platform:
        match platform.system():
            case 'Android': return Platform.Android
            case 'Darwin':  return Platform.MacOS
            case 'iOS':     return Platform.iOS
            case 'iPadOS':  return Platform.iOS
            case 'Linux':   return Platform.Linux
            case 'Windows': return Platform.Windows

    @staticmethod
    def get_available_choices() -> [Platform]:
        return [
            Platform.Linux,
            Platform.Web,
            Platform.Windows,
        ]