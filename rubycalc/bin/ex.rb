#!/usr/bin/env ruby
require 'getoptlong'
require 'stringio'

opts = GetoptLong.new(
  [ '--variable', '-v', GetoptLong::REQUIRED_ARGUMENT ],  
)

word = 0
a = "add"
b = ""
arg_dup = ARGV[0].dup
opts.each do |opt, arg|
  case opt
  when '--variable'
    word = arg
    b = word.chomp(";")
    b = b.partition("=")
    puts "key : #{b.first}, value: #{b.last}"
  end
end

#arg_dup = ARGV[0].dup

#ARGV.each do |value|
 # word += value.concat(a)
#end



    
