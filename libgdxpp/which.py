import subprocess
import os
import platform

from pathlib import Path

def which(name: str) -> Path:
    platform_which = 'which'
    if platform.system() == 'Windows':
        platform_which = 'where'

    try:
        result: str = subprocess.check_output([platform_which, name]).decode('utf-8').strip()
        resolved_path = Path(result).resolve()
        return resolved_path
    except:
        return None