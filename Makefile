build_stuff:
	@echo "Building ..."
	sleep 1
	nasm -felf64 out.asm
	ld out.o -o out
	@echo "Done !"

generate:
	@echo "I dont know ..."
clean:
	@echo "Cleaning up..."
	rm out.asm out.o out
	@echo "Done !"
run:
	./out
