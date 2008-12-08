#!/usr/bin/perl  -w

use strict;

my $outstart = 0;



sub usage()
{
  print "usage: [-p <varname>] <filename> [|<filename> [|...]]\n";
}



sub stringstart($)
{
  my ($varname) = @_;

  if ($outstart)
  {
    print ";\n";
  }
  print "const char * $varname =\n";
  $outstart = 1;
}



while (@ARGV)
{
  if ($ARGV[0] eq "-p")
  {
    shift @ARGV;
    my $varname = shift @ARGV;
    stringstart($varname);
  }

  my $filname = shift @ARGV;

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

    if ($line =~ /\/\*stringname: .*\*\//)
    {
      stringstart substr($line, 14, length($line)-17);
      next;
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
