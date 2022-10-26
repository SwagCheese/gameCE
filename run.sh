PGM_NAME=$(< makefile sed -z 's/\(\(.*\n\)*NAME\ =\ \)//' | head -1)
make clean
if ! make gfx || ! make; then
    read -r -p "Making ${PGM_NAME} resulted in an error. Running the program will launch the last successful build. Continue? [y/N]" response
    case "$response" in
    [yY][eE][sS]|[yY]) 
        ;;
    *)
        exit 0
        ;;
    esac
fi
cemu -s bin/*.8xp --launch "$PGM_NAME"