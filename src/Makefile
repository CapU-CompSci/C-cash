all: cunit punit bunit

cunit: credential.h credential.c cred-test-unit.c
	gcc credential.c cred-test-unit.c -o cunit

punit: puzzle.h puzzle.c puzzle-test-unit.c
	gcc puzzle.c puzzle-test-unit.c sha1/sha1.c -o punit

bunit: puzzle.h puzzle.c credential.h credential.c block.h block.c block-test-unit.c
	gcc puzzle.c credential.c block.c block-test-unit.c sha1/sha1.c -o bunit

clean:
	@rm -f *.o cunit punit bunit