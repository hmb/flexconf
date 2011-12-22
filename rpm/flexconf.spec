Name:           flexconf
#Conflicts:
Version:        0.9.1.0
Release:        1
Summary:        flexconf is a flexible configuration generator for C++
Group:          Development/Tools
License:        GPL
Vendor:         Amarin Software
AutoReqProv:    on
#PreReq:         
#Requires:       
Source:         %{name}_%{version}-%{release}.tar.gz
BuildRequires:  automake
BuildRequires:  make
BuildRequires:  gcc-c++
BuildRequires:  libtool
BuildRequires:  flex
BuildRequires:  bison
BuildRequires:  libxml2-devel
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%define flexconf_bin            %_bindir
%define flexconf_dat            %_datadir/flexconf
%define flexconf_man            %_mandir/man1

%description
flexconf is a flexible configuration generator the takes C++ structs as input
and generates custom serializers and deserializers. An inbuild version exists
for the generation of xml, json and windows registry.


######################################################################
# prep
######################################################################
%prep
%setup -q


######################################################################
# build
######################################################################
%build

./do_autoconf
%{__make}


######################################################################
# install
######################################################################
%install

# Binaries
install -d %{buildroot}%{flexconf_bin}
install -m 755 src/flexconf %{buildroot}%{flexconf_bin}/flexconf

install -d %{buildroot}%{flexconf_dat}
install -m 644 src/gencust/xmlconf.src %{buildroot}%{flexconf_dat}/xmlconf.src
install -m 644 src/gencust/libxml2.src %{buildroot}%{flexconf_dat}/libxml2.src
install -m 644 src/gencust/json.src %{buildroot}%{flexconf_dat}/json.src

install -d %{buildroot}%{flexconf_man}
install -m 0644 doc/flexconf.txt %{buildroot}%{flexconf_man}/flexconf.1
gzip %{buildroot}%{flexconf_man}/flexconf.1


######################################################################
# clean
######################################################################
%clean
%{__rm} -rf %{buildroot}


######################################################################
# post
######################################################################
%post


######################################################################
# files
######################################################################
%files
%defattr(-,root,root,-)

#%config %{apache2_sysconf_dir}

%{flexconf_bin}
%{flexconf_bin}/flexconf

%{flexconf_dat}
%{flexconf_dat}/xmlconf.src
%{flexconf_dat}/libxml2.src
%{flexconf_dat}/json.src

%doc AUTHORS
%doc ChangeLog
%doc COPYING
%doc NEWS
%doc README
%doc %{flexconf_man}
%doc %{flexconf_man}/flexconf.1.gz
