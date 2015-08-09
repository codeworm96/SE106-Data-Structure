total = 10
point = 0
(1..total).each{|i|
  system './sort <sort'+i.to_s+'.in >sort.out'
  if system 'diff ./sort.out ./sort'+i.to_s+'.ans'
    point+=1
  else
    break
  end
}
puts point.to_s+'/'+total.to_s
