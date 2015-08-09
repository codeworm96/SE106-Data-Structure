res = 0
#(1..200).each {
  File.open("hash.in","w"){ |f|
    f.puts 100000
    f.puts 50000
    (1..100000).to_a.shuffle!.each{|x|
      f.puts x
    }
  }
  system "./hash"
  #system "./hash_trival"
  if system "diff ./hash.ans ./hash.out"
    res += 1
  else
  #  break
  end
  puts res
#}
puts "end, ", res
