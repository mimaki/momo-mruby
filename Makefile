MRUBY = ./mruby

all:
	ruby patch-mruby.rb
	MRUBY_CONFIG=../mbed_build_config.rb make -C $(MRUBY)
	$(MRUBY)/bin/mrbc -Bappbin -o app.c app.rb
	mbed compile
	ruby unpatch-mruby.rb

test:
	ruby patch-mruby.rb
	MRUBY_CONFIG=../mbed_build_config.rb make -C $(MRUBY) test
	ruby unpatch-mruby.rb

clean:
	make -C $(MRUBY) clean
	rm -rf mruby/build
	rm -f app.c
	ruby unpatch-mruby.rb
