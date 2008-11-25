BEGIN {
  BS = "\\\\"
  print "const char * " STRNAME " ="
}

{ gsub(/\\/,  BS BS); }
{ gsub(/\t/,  BS "\t"); }
{ gsub(/\n/,  BS "\n"); }
{ gsub(/\"/,  BS "\""); }
{ print "  \"" $0 "\\n\"" }

END {
  print ";"
}
