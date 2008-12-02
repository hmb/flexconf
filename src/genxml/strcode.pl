#!/usr/bin/perl  -w

my $count = @ARGV;

if ($count < 2)
{
  print "usage: <varname> <filename> [|<filename> [|...]]\n";
  exit;
}

$varname = shift @ARGV;

print "const char * $varname =\n";

while ($filname = shift @ARGV)
{
  if (! -f $filname)
  {
    print "file \"$filname\" not found...\n";
    exit;
  }

  if (!open(INFIL, "<$filname"))
  {
    print "file \"$filname\" could not be opened...\n";
    exit;
  }

  my @infile  = <INFIL>;
  my $start   = 1;

  foreach my $line (@infile)
  {
    # skip c++ comments at the beginning of the file
    if ($start)
    {
      if ($line =~ /^\/\//)
      {
        next;
      }

      $start = 0;
    }

    $line =~ s/\\/\\\\/g;
    $line =~ s/"/\\"/g;
    $line =~ s/\t/\\t/g;
    $line =~ s/\n/\\n/g;
    print "  \"$line\"\n";
  }

  close INFIL;
}

print ";\n";
