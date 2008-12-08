#!/usr/bin/perl  -w

use strict;

my $insection = 0;



sub usage()
{
  print "usage: [-p <varname>] <filename> [|<filename> [|...]]\n";
}



sub beginsection($)
{
  my ($varname) = @_;

  endsection();
  print "const char * psz$varname =\n";
  $insection = 1;
}



sub endsection()
{
  if ($insection)
  {
    print ";\n";
  }
  $insection = 0;
}



while (@ARGV)
{
  if ($ARGV[0] eq "-p")
  {
    shift @ARGV;
    my $varname = shift @ARGV;
    beginsection $varname;
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

  my @infile    = <INFIL>;
  my $filestart = 1;

  foreach my $line (@infile)
  {
    if ($filestart)
    {
      # skip c++ comments at the beginning of the file
      if ($line =~ /^\/\//)
      {
        next;
      }
      $filestart = 0;
    }

    if ($line =~ /\/\* *begin section: *([_a-zA-Z][_a-zA-Z0-9]*) *\*\//)
    {
      beginsection $1;
      next;
    }

    if ($line =~ /\/\* *end section *\*\//)
    {
      endsection();
      next;
    }

    if (!$insection)
    {
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

endsection();
