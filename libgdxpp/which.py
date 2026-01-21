import subprocess
import os
import platform

from pathlib import Path
from libgdxpp.stdio import *

__is_windows__ = platform.system() == 'Windows'

def __which(name: str, platform_which: str) -> Path:
    try:
        result: str = subprocess.check_output(
            [platform_which, name],
            stderr=subprocess.PIPE,
        ).decode('utf-8').strip()
        resolved_path = Path(result).resolve()
        return resolved_path
    except Exception as err:
        if platform_which == 'where':
            return __which(name, 'which')
        elif __is_windows__:
            print_warning('Failed to use where/which to get the exact path of "%s":\n\t%s' % (
                name,
                err,
            ))
            return name
        return None

def which(name: str) -> Path:
    platform_which = 'which'
    if __is_windows__:
        platform_which = 'where'

    return __which(name, platform_which)