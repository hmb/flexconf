#!/usr/bin/perl  -w

use strict;

sub usage()
{
  print "usage: [-p <varname>] <filename> [|<filename> [|...]]\n";
}



my $outstart = 0;

while (@ARGV)
{

  if ($ARGV[0] eq "-p")
  {
    shift @ARGV;
    my $varname = shift @ARGV;

    if ($outstart)
    {
      print ";\n";
    }
    print "const char * $varname =\n";
  }

  $outstart = 1;

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

    $line =~ s/\\/\\\\/g;
    $line =~ s/"/\\"/g;
    $line =~ s/\t/\\t/g;
    $line =~ s/\n/\\n/g;
    print "  \"$line\"\n";
  }

  close INFIL;
}

print ";\n";
