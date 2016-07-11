Compression: Compression.cc bitstream.o bitstream.h huffman_tree.o huffman_tree.h
	g++ -o $@ Compression.cc bitstream.o huffman_tree.o -Wall -O2
bitstream.o: bitstream.h bitstream.cpp
	g++ -c bitstream.cpp -o bitstream.o -Wall -O2
huffman_tree.o: huffman_tree.h huffman_tree.cpp
	g++ -c huffman_tree.cpp -o huffman_tree.o -Wall -O2
clean:
	rm *.o *.tmp Compression -f
