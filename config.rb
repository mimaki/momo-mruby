app_config = Proc.new {
  puts "Application setting..."
}
mrdb_config = Proc.new {
  puts "mrdb setting..."
}
mirb_config = Proc.new {
  puts "mirb setting..."
}
ipv4_config = Proc.new {
  puts "IPv4 setting..."
}
exit_menu = Proc.new {
  'exit'
}

mainmenu = {
  'A' => {:menu=>'Application setting',               :proc=>app_config},
  # 'D' => {:menu=>'mruby debugger setting',            :proc=>mrdb_config},
  # 'I' => {:menu=>'Interactive mruby (mirb) setting',  :proc=>mirb_config},
  # 'P' => {:menu=>'IPv4 setting',                      :proc=>ipv4_config},
  'X' => {:menu=>'Exit configuration menu',           :proc=>exit_menu},
}

while true
  puts "\n<< Configuration MENU >>"
  mainmenu.each {|cmd|
    puts "#{cmd[0]}: #{cmd[1][:menu]}"
  }
  print "> "
  cmd = gets.chomp
  if menu = mainmenu[cmd[0].upcase]
    ret = menu[:proc].call
    break if ret == 'exit'
  end
end
