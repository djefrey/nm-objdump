##
## EPITECH PROJECT, 2022
## B-PSU-400-STG-4-1-nmobjdump-jeffrey.winkler
## File description:
## Makefile
##

COMMON_SRC			=	src/common/elf.c				\
						src/common/archive.c			\
						src/common/section_32.c			\
						src/common/section_64.c			\
						src/common/strtab.c				\
						src/common/error.c

NM_SRC				=	src/nm/main.c					\
						src/nm/nm.c						\
						src/nm/symbols_32.c				\
						src/nm/symbols_64.c				\
						src/nm/icon_32.c				\
						src/nm/icon_64.c				\
						src/nm/icon_section_32.c		\
						src/nm/icon_section_64.c		\
						src/nm/sections.c				\
						src/nm/name.c

OBJDUMP_SRC			=	src/objdump/main.c				\
						src/objdump/objdump.c			\
						src/objdump/infos.c				\
						src/objdump/dump.c				\
						src/objdump/flags_32.c			\
						src/objdump/flags_64.c			\
						src/objdump/utils.c				\
						src/objdump/name.c

INC_DIR				=	./include

CFLAGS				+=	-I$(INC_DIR)

MYLIB				=	./mylib

COMMON_OBJ			=	$(COMMON_SRC:.c=.o)
NM_OBJ				=	$(NM_SRC:.c=.o)
OBJDUMP_OBJ			=	$(OBJDUMP_SRC:.c=.o)

NM_NAME				=	my_nm
OBJDUMP_NAME		=	my_objdump

all: nm objdump

nm: $(COMMON_OBJ) $(NM_OBJ)
	make -C $(MYLIB) all
	gcc $(CFLAGS) -o $(NM_NAME) $(COMMON_OBJ) $(NM_OBJ) -L$(MYLIB) -lmy

objdump: $(COMMON_OBJ) $(OBJDUMP_OBJ)
	make -C $(MYLIB) all
	gcc $(CFLAGS) -o $(OBJDUMP_NAME) $(COMMON_OBJ) $(OBJDUMP_OBJ) -L$(MYLIB) -lmy

debug: CFLAGS += -g
debug: re

clean:
	make -C $(MYLIB) clean
	rm -f $(COMMON_OBJ)
	rm -f $(NM_OBJ)
	rm -f $(OBJDUMP_OBJ)

fclean: clean
	make -C $(MYLIB) fclean
	rm -f $(NM_NAME)
	rm -f $(OBJDUMP_NAME)

re: fclean all