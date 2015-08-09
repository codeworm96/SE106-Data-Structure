total = 10
(1..total).each{|i|
  system './std <sort'+i.to_s+'.in >sort'+i.to_s+'.ans'
}
