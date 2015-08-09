prog = ARGV[0]
score = 0
(0..9).each do |i|
  if system "timeout 1 #{prog} <./trace/trace0#{i}.txt >res"
    if system "diff ./trace/ans0#{i}.txt res"
      score += 1
    end
  end
  `rm res`
end

puts score
