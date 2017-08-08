# /sd/mruby.cfg
#---------
# mirb=0/1
# mrdb=0/1
# STDOUT=0/1
# STDIN=0/1
# LAN_DHCP=0/1
# LAN_IPADDR=xxx.xxx.xxx.xxx
# LAN_SUBNET=xxx.xxx.xxx.xxx
# LAN_GATEWAY=xxx.xxx.xxx.xxx

CFGKEYS = [
  'mirb',
  'mrdb',
  'STDOUT',
  'STDIN',
  # 'LAN_DHCP',
  # 'LAN_IPADDR',
  # 'LAN_SUBNET',
  # 'LAN_GATEWAY',
]

CFGFILE     = '/sd/mruby.cfg'
PRELOADFILE = '/sd/preload'

def load_config
  cfg = {
    :mirb => 1,
    :mrdb => 0,
    :stdout => 1,
    :stdin => 1,
    :lan_dhcp => 1,
    :lan_ipaddr => '192.168.1.100',
    :lan_subnet => '255.255.255.0',
    :lan_gateway => '192.168.1.1'
  }
  begin
    File.open(CFGFILE, 'r') {|f|
      while line = f.gets
        kv = line.chomp.split('=').each {|v| v.strip!}
        cfg[kv[0].downcase.to_sym] = kv[1] unless kv[0][0] == '#'
      end
    }
  rescue
  end
  $appcfg = cfg
end

def save_config
  File.open(CFGFILE, 'w') {|f|
    CFGKEYS.each {|k|
      f.puts "#{k}=#{$appcfg[k.downcase.to_sym]}"
    }
  }
rescue => e
  puts e
end

def input_01(prompt, cur)
  loop {
    print "#{prompt} (#{cur}) => "
    v = gets.chomp.strip
    return cur.to_i if v.size == 0
    return v.to_i if v =='0' or v == '1'
    return nil if v.downcase == 'q'
  }
end

exit_menu = Proc.new {
  'exit'
}

# Application setting...
# Enable mirb (1) => 0/1
# Enable mruby debugger (0) => 0/1
# Enable STDOUT via VCP (1) => 0/1
# Enable STDIN via VCP (1) => 0/1
app_config = Proc.new {
  puts "Application setting..."
  cfg = load_config
  [
    [:mirb,     'Enable mirb'],
    [:mrdb,     'Enable mruby debugger'],
    [:stdout,   'Enable STDOUT via VCP'],
    [:stdin,    'Enable STDIN via VCP'],
    # [:lan_dhcp, 'Enable DHCP on LAN']
  ].each {|kv|
    cfg[kv[0]] = input_01(kv[1], cfg[kv[0]])
  }
  $appcfg = cfg
  save_config
}

def load_preload_modules
  mods = []
  begin
    File.open(PRELOADFILE, 'r') {|f|
      while l = f.gets
        mod = l.chomp.strip
        mods << mod if mod.size > 0 && mod[0] != '#'
      end
    }
  rescue
  end
  mods
end

add_preload_module = Proc.new {|mods|
  print "MRB file : "
  mrb = gets.chomp
  mods << mrb if mrb.size > 0
  mods
}

remove_preload_module = Proc.new {|mods|
  print "Remove module number : "
  no = gets.chomp.to_i
  mods.delete_at(no - 1) if no > 0
  mods
}

save_preload_module = Proc.new {|mods|
  begin
    File.open(PRELOADFILE, 'w') {|f|
      mods.each {|mod|
        f.puts mod
      }
    }
  rescue => e
    puts e
  end
  'exit'
}

# Preload module setting...
# <Preload modules>
#   1) hoge.mrb
#   2) fuga.mrb
# ------------------
# A: Add preload module
# R: Remove preload module
# X: Save and exit
# Q: Quit without save
preload_config = Proc.new {
  puts "Preload module setting..."
  mods = load_preload_modules
  loop {
    puts "<Preload modules>"
    mods.each_with_index {|m, i| puts "  #{i+1}) #{m}"}
    puts "  none." if mods.size == 0
    puts "-----------------"
    preload_menu = {
      'A' => {:menu=>'Add preload module',    :proc=>add_preload_module},
      'R' => {:menu=>'Remove preload module', :proc=>remove_preload_module},
      'X' => {:menu=>'Save and exit',         :proc=>save_preload_module},
      'Q' => {:menu=>'Quit without save',     :proc=>exit_menu}
    }
    preload_menu.each {|cmd|
      puts "#{cmd[0]}: #{cmd[1][:menu]}"
    }
    print "> "
    cmd = gets.chomp
    if cmd.size > 0
      if menu = preload_menu[cmd[0].upcase]
        ret = menu[:proc].call(mods)
        break if ret == 'exit'
        mods = ret
      end
    end
  }
}


# mrdb_config = Proc.new {
#   puts "mrdb setting..."
# }
# mirb_config = Proc.new {
#   puts "mirb setting..."
# }
# ipv4_config = Proc.new {
#   puts "IPv4 setting..."
# }

# load mruby.cfg
load_config

begin
  if $menu
    main_menu = {
      'A' => {:menu=>'Application setting',               :proc=>app_config},
      # 'D' => {:menu=>'mruby debugger setting',            :proc=>mrdb_config},
      # 'I' => {:menu=>'Interactive mruby (mirb) setting',  :proc=>mirb_config},
      'P' => {:menu=>'Preload module setting',            :proc=>preload_config},
      # 'L' => {:menu=>'LAN IPv4 setting',                  :proc=>ipv4_config},
      'X' => {:menu=>'Exit configuration menu',           :proc=>exit_menu},
    }

    loop {
      puts "\n<< Configuration MENU >>"
      main_menu.each {|cmd|
        puts "#{cmd[0]}: #{cmd[1][:menu]}"
      }
      print "> "
      cmd = gets.chomp
      if cmd.size > 0
        if menu = main_menu[cmd[0].upcase]
          ret = menu[:proc].call
          break if ret == 'exit'
        end
      end
    }
  end
rescue => e
  puts e
end
