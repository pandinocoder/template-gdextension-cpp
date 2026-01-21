from colorama import Fore, Style
from os import linesep
from sys import stderr, stdout

def indent_lines(*lines: str, indent = '\t'):
    indented_lines = []
    for line in lines:
        parts = line.splitlines()
        indented_parts = [(indent + l) for l in parts]
        indented_line = linesep.join(indented_parts)
        indented_lines.append(indented_line)
    return indented_lines

def __stringify(*values: object) -> tuple:
    return map(
        lambda v: v if isinstance(v, str) else str(v),
        values
    )

def __print(
    *values: object,
    sep: Optional[str] = ' ',
    end: Optional[str] = linesep,
    file: Optional[SupportsWrite[str]] = stdout,
    flush: bool = False,
    prefix: str = '',
    suffix: str = ''
) -> None:
    message = prefix + sep.join(*values) + suffix + Style.RESET_ALL + end
    file.write(message)
    if flush:
        file.flush()

def print_debug(
    *values: object,
    sep: Optional[str] = ' ',
    end: Optional[str] = linesep,
    file: Optional[SupportsWrite[str]] = stdout,
    flush: bool = False,
) -> None:
    __print(values, sep=sep, end=end, file=file, flush=flush,
        prefix=Style.DIM,
    )

def print_info(
    *values: object,
    sep: Optional[str] = ' ',
    end: Optional[str] = linesep,
    file: Optional[SupportsWrite[str]] = stdout,
    flush: bool = False,
    dim: bool = False,
) -> None:
    __print(values, sep=sep, end=end, file=file, flush=flush,
        prefix=Style.RESET_ALL + (Style.DIM if dim else ''),
    )

def print_notice(
    *values: object,
    sep: Optional[str] = ' ',
    end: Optional[str] = linesep,
    file: Optional[SupportsWrite[str]] = stdout,
    flush: bool = False,
    dim: bool = False,
) -> None:
    __print(values, sep=sep, end=end, file=file, flush=flush,
        prefix=Fore.LIGHTBLUE_EX + (Style.DIM if dim else ''),
    )

def print_success(
    *values: object,
    sep: Optional[str] = ' ',
    end: Optional[str] = linesep,
    file: Optional[SupportsWrite[str]] = stdout,
    flush: bool = False,
    dim: bool = False,
) -> None:
    __print(values, sep=sep, end=end, file=file, flush=flush,
        prefix=Fore.GREEN + (Style.DIM if dim else ''),
    )

def print_warning(
    *values: object,
    sep: Optional[str] = ' ',
    end: Optional[str] = linesep,
    file: Optional[SupportsWrite[str]] = stdout,
    flush: bool = False,
    dim: bool = False,
) -> None:
    __print(values, sep=sep, end=end, file=file, flush=flush,
        prefix=Fore.YELLOW + (Style.DIM if dim else ''),
    )

def print_error(
    *values: object,
    sep: Optional[str] = ' ',
    end: Optional[str] = linesep,
    file: Optional[SupportsWrite[str]] = stderr,
    flush: bool = False,
    dim: bool = False,
) -> None:
    __print(values, sep=sep, end=end, file=file, flush=flush,
        prefix=Fore.RED + (Style.DIM if dim else ''),
    )