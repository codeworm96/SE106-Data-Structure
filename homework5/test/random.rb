total = 100
point = 0
(1..total).each{|i|
  system './creator > sort.in'
  system './sort <sort.in >sort.out'
  system './std <sort.in >sort.ans'
  if system 'diff ./sort.ans ./sort.out'
    point+=1
  end
}
puts point
