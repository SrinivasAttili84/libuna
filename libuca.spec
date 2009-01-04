Name: libuca
Version: 20080831
Release: 1
Summary: Library to support Unicode and ASCII conversions
Group: System Environment/Libraries
License: LGPL
Source: %{name}-%{version}.tar.gz
URL: https://www.uitwisselplatform.nl/projects/libuca
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: sg3_utils-devel
Requires: sg3_utils-libs

%description
libuca is a library to support Unicode and ASCII conversions

%package devel
Summary: Header files and libraries for developing applications for libuca
Group: Development/Libraries
Requires: libuca = %{version}-%{release}

%description devel
Header files and libraries for developing applications for libuca.

%package tools
Summary: Several tools for converting Unicode and ASCII based text
Group: Applications/System
Requires: libuca = %{version}-%{release}

%description tools
Several tools for converting Unicode and ASCII based text

%prep
%setup -q

%build
%configure --prefix=/usr --libdir=%{_libdir} --mandir=%{_mandir}
make %{?_smp_mflags}

%install
rm -rf ${RPM_BUILD_ROOT}
make DESTDIR=${RPM_BUILD_ROOT} install

%clean
rm -rf ${RPM_BUILD_ROOT}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(644,root,root,755)
%doc AUTHORS COPYING NEWS README
%attr(755,root,root) %{_libdir}/*.so.*

%files devel
%defattr(644,root,root,755)
%doc AUTHORS COPYING NEWS README ChangeLog
%{_libdir}/*.a
%{_libdir}/*.la
%{_libdir}/*.so
%{_libdir}/pkgconfig/libuca.pc
%{_includedir}/*
%{_mandir}/man3/*

%files tools
%defattr(644,root,root,755)
%doc AUTHORS COPYING NEWS README
%attr(755,root,root) %{_bindir}/ucaexport
%{_mandir}/man1/*

%changelog
* Fri Aug 29 2008 Joachim Metz <forensics@hoffmannbv.nl> 20080829-1
- Initial version based on libpff spec file
