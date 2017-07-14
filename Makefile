MRUBY = ./mruby

all:
	mbed deploy
	ruby patch-mruby.rb
	MRUBY_CONFIG=../mbed_build_config.rb make -C $(MRUBY)
	$(MRUBY)/bin/mrbc -Bappbin -o $(MRUBY)/build/app.c app.rb
	$(MRUBY)/bin/mrbc -Bcfgmenu -o $(MRUBY)/build/config.c config.rb
	mbed compile
	ruby unpatch-mruby.rb

test:
	ruby patch-mruby.rb
	MRUBY_CONFIG=../mbed_build_config.rb make -C $(MRUBY) test
	ruby unpatch-mruby.rb

clean:
	make -C $(MRUBY) clean
	rm -rf $(MRUBY)/build
	ruby unpatch-mruby.rb
