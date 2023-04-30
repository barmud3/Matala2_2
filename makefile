all: copy cmp encode decode


copy: copy.c
	gcc copy.c -o copy
cmp: cmp.c
	gcc cmp.c -o cmp
encode: encode.c libCodecA libCodecB
	gcc encode.c -L. -l CodecA -l CodecB -o encode
decode: decode.c libCodecB libCodecB
	gcc decode.c -L. -l CodecA -l CodecB -o decode
libCodecA: sensetive.c
	gcc -o libCodecA.so -shared -fpic sensetive.c
libCodecB: 3-rdNext.c
	gcc -o libCodecB.so -shared -fpic 3-rdNext.c
