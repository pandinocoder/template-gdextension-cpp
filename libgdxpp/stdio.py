from colorama import ansi, Fore, Style
from os import linesep
from sys import stderr, stdout

STYLE_ITALIC = ansi.code_to_chars(3)
STYLE_NO_ITALIC = ansi.code_to_chars(23)
STYLE_UNDERLINE = ansi.code_to_chars(4)
STYLE_NO_UNDERLINE = ansi.code_to_chars(24)

def italic(text: str) -> str:
    return STYLE_ITALIC + text + STYLE_NO_ITALIC

def underline(text: str) -> str:
    return STYLE_UNDERLINE + text + STYLE_NO_UNDERLINE

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
        prefix=Fore.LIGHTBLACK_EX + '[DBG] ' + STYLE_ITALIC,
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
        prefix=Style.RESET_ALL + (Style.DIM if dim else '') + '[INF] ',
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
        prefix=Fore.LIGHTBLUE_EX + (Style.DIM if dim else '') + '[INF] ',
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
        prefix=Fore.GREEN + (Style.DIM if dim else '') + '[OK] ',
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
        prefix=Fore.YELLOW + (Style.DIM if dim else '') + '[WRN] ',
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
        prefix=Fore.RED + (Style.DIM if dim else '') + '[ERR] ',
    )

def print_fatal(
    *values: object,
    sep: Optional[str] = ' ',
    end: Optional[str] = linesep,
    file: Optional[SupportsWrite[str]] = stderr,
    flush: bool = False,
    dim: bool = False,
    exit_code: int = 1,
) -> None:
    __print(values, sep=sep, end=end, file=file, flush=flush,
        prefix=Fore.RED + (Style.DIM if dim else '') + '[FTL] ',
    )
    exit(exit_code)