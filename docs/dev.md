# Developer Notes

## Logging & Error Handling Conventions

Logging
- Use the logging helpers in `core/log.h` for user-facing messages.
- Levels:
  - ERROR: failures that prevent the CLI from completing the command.
  - WARN: recoverable issues or partial results.
  - INFO: high-level progress and normal status.
  - DEBUG: detailed diagnostics for development.
- Log output format is `[LEVEL] message`.
- ERROR/WARN go to stderr; INFO/DEBUG go to stdout.

Error handling
- Functions return a status or error code; only the CLI decides the process exit.
- CLI exit codes (defined in `core/errors.h`):
  - `EXIT_OK` (0): success.
  - `EXIT_INVALID_ARGS` (2): invalid CLI usage or parse errors.
  - `EXIT_RUNTIME_ERROR` (3): runtime failures.
- When you detect an error:
  - Log the error with ERROR level.
  - Return a non-zero error code to the caller.
