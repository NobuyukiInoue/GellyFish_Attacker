#!/usr/bin/perl

use File::Basename;
use POSIX 'strftime';
use strict;
use warnings;
use Time::HiRes 'sleep';

my $scriptName = basename($0, '');
my $targetHostName;
my $targetPort;

if ( @ARGV == 1 ) {
    my @flds = split(':', $ARGV[0]);
    $targetHostName = $flds[0];
    $targetPort = $flds[1];
}
else {
    print("Usage: $scriptName target_HostName:Port\n");
    exit(1);
}

&cls();
&monitor();

sub monitor()
{
    my @sendBytes = (
        32, 48, 64, 72, 96, 128, 144, 192, 224, 240,
        256, 512, 1024, 1200, 1216, 1220, 1320, 1440,
        1472, 1500, 1512, 1518, 1582, 2048, 4096,
        16384, 32268, 65535
    );

    my $sendBytes_Length = @sendBytes;

    #for (my $count = 0; $count < 1000; $count++ ) {
    while(1) {
        &locate(1,1);
        #my $localtime = strftime("%Y/%m/%d %H:%M:%S", localtime);
        my $localtime = strftime("%Y/08/%d %H:%M:%S", localtime);
        print($localtime);

        my $i;
        my $tempStr;

        &locate(2,1);
        set_BackColor("green", "JellyFisy");

        for ($i = 1; $i <= 10; $i++ ) {
            &locate(2 + $i, 1);
            $tempStr = sprintf("JellyFish:%d ----", get_PortNum());
            set_ForeColor("green", $tempStr);
        }

        &locate(2,25);
        set_BackColor("sky", "Proxy-Step1");

        for ($i = 1; $i <= 20; $i++ ) {
            &locate(2 + $i, 20);
            set_ForeColor("sky", "+---");
        }

        for ($i = 1; $i <= 20; $i++ ) {
            &locate(2 + $i, 25);
            $tempStr = sprintf("Proxy%03d:%5d ---+--- ", $i, get_PortNum(), @sendBytes[int(rand($sendBytes_Length))] );
            set_ForeColor("sky", $tempStr);
            #set_BackColor("sky", $tempStr);
        }

        &locate(2,48);
        set_BackColor("yellow", "Proxy-Step2");

        for ($i = 1; $i <= 50; $i++ ) {
            &locate(2 + $i, 48);
            $tempStr = sprintf("Proxy%03d:%5d ---(%6d Bytes)--> ", $i, get_PortNum(), @sendBytes[int(rand($sendBytes_Length))] );
            set_ForeColor("yellow", $tempStr);
            #set_BackColor("yellow", $tempStr);
        }

        &locate(2,85);
        set_BackColor("red", $targetHostName);

        for ($i = 1; $i <= 50; $i++ ) {
            &locate(2 + $i, 85);
            set_ForeColor("red", $targetHostName.":".$targetPort);
            #set_BackColor("red", $targetHostName);
        }


        sleep(1);
        #print("Hit Any Key");
        #getc();
    }

    print("\n");
    &locate(31,1);
}

sub test_print1()
{
    &set_ForeColor("black", "test\n");
    &set_ForeColor("red", "test\n");
    &set_ForeColor("green", "test\n");
    &set_ForeColor("yellow", "test\n");
    &set_ForeColor("blue", "test\n");
    &set_ForeColor("magenta", "test\n");
    &set_ForeColor("sky", "test\n");
    &set_ForeColor("white", "test\n");
    &set_ForeColor("other", "test\n");
}

sub test_print2()
{
    &set_BackColor("black", "test\n");
    &set_BackColor("red", "test\n");
    &set_BackColor("green", "test\n");
    &set_BackColor("yellow", "test\n");
    &set_BackColor("blue", "test\n");
    &set_BackColor("magenta", "test\n");
    &set_BackColor("sky", "test\n");
    &set_BackColor("white", "test\n");
    &set_BackColor("other", "test\n");
}

sub cls() {
    print("\e[2J");
}

sub locate(){
    printf("\e[%d;%dH", $_[0], $_[1])
}

sub set_ForeColor {
    if ($_[0] eq "black") {
        printf("\e[30m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "red") {
        printf("\e[31m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "green") {
        printf("\e[32m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "yellow") {
        printf("\e[33m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "blue") {
        printf("\e[34m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "magenta") {
        printf("\e[35m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "sky") {
        printf("\e[36m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "white") {
        printf("\e[37m%s\e[m", $_[1]);
    }
    else {
        printf("\e[37m%s\e[m", $_[1]);
    }
}

sub set_BackColor {
    if ($_[0] eq "black") {
        printf("\e[40m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "red") {
        printf("\e[41m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "green") {
        printf("\e[42m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "yellow") {
        printf("\e[43m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "blue") {
        printf("\e[44m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "magenta") {
        printf("\e[45m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "sky") {
        printf("\e[46m%s\e[m", $_[1]);
    }
    elsif ($_[0] eq  "white") {
        printf("\e[47m%s\e[m", $_[1]);
    }
    else {
        printf("\e[40m%s\e[m", $_[1]);
    }
}

sub get_PortNum()
{
    my $portNum = 0;
    while ($portNum < 9000) {
        $portNum = int(rand(65535));
    }

    return $portNum;
}
