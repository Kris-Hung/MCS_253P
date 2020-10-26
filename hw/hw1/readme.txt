Terminal Commands:

# Compile
g++ MusicLibrary.cpp -o MusicLibrary

# Case with default music library
valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes MusicLibrary

# Case with music library given by input
valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes MusicLibrary summer_music