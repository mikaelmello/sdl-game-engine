id="$(git branch | grep \* | cut -d '-' -f2)"
matricula="160015537"

zip "$matricula""_T$id.zip" src/* obj/.gitkeep include/* Makefile README.md
