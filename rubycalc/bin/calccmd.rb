#!/usr/bin/env ruby
require 'getoptlong'
require 'stringio'
opts = GetoptLong.new(
  #['--sum ', '-s', GetoptLong::REQUIRED_ARGUMENT],
  #['--times ', '-t', GetoptLong::REQUIRED_ARGUMENT]
  ['--variable ', '-e', GetoptLong::REQUIRED_ARGUMENT]
)

sum = 0
times = 1
b = ""
opts.each do |opt, arg|
  case opt
  when '--sum '
    sum += arg.to_i
  when '--times '
    times *= arg.to_i
  when '--variable '
    b = arg
  end
end

ARGV.each do |value|
  sum += value.to_i
  times *= value.to_i
end

puts "sum: #{sum} times: #{times} var: #{b}"
