CC = gcc
CFLAGS = -Wall -Wextra -g
MKSTR = $(CC) $@.c -o bin/$@ $(CFLAGS)

all: ex_1 ex_3 ex_4 ex_5 ex_6 ex_7 ex_8 ex_9 ex_10 ex_11 ex_12 ex_13 ex_14 ex_15 ex_16 ex_17 stack ex_18 ex_19_dir ex_20 ex_22_dir ex_23 ex_24 ex_25 ex_26_dir ex_27

ex_1:
	$(MKSTR)

ex_3:
	$(MKSTR)

ex_4:
	$(MKSTR)

ex_5:
	$(MKSTR)

ex_6:
	$(MKSTR)

ex_7:
	$(MKSTR)

ex_8:
	$(MKSTR)

ex_9:
	$(MKSTR)

ex_10:
	$(MKSTR)

ex_11:
	$(MKSTR)

ex_12:
	$(MKSTR)

ex_13:
	$(MKSTR)

ex_14:
	$(MKSTR)

ex_15:
	$(MKSTR)

ex_16:
	$(MKSTR)

ex_17:
	$(MKSTR)

stack:
	$(MKSTR)

ex_18:
	$(MKSTR)

ex_19_dir:
	make -C ex_19/

ex_20:
	$(MKSTR)

ex_22_dir:
	make -C ex_22/

ex_23:
	$(MKSTR)

ex_24:
	$(MKSTR)

ex_25:
	$(MKSTR)

ex_26_dir:
	make -C ex_26/

ex_27:
	$(MKSTR)

clean: remove_temp
	rm -f bin/*
	make clean -C ex_19/
	make clean -C ex_22/
	make clean -C ex_26/

remove_temp:
	rm -f *~
	make remove_temp -C ex_19/
	make remove_temp -C ex_22/
	make remove_temp -C ex_26/
