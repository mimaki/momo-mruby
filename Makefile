MRUBY = ./mruby

all:
	MRUBY_CONFIG=../mbed_build_config.rb make -C $(MRUBY)
	$(MRUBY)/bin/mrbc -Bappbin -o app.c app.rb
	mbed compile

clean:
	make -C $(MRUBY) clean
	rm -rf mruby/build
	rm -f app.c
