# Migrating to libstdc++ and Testing

These are just some notes/ruminations on the process of moving to libstdc++ with this implementation.

## Namespace

For libstdc++, the detail namespace is `__gnu_cxx::`.


## Variable and Writing conventions

This library keeps to the [libstdc++ naming conventions](https://gcc.gnu.org/onlinedocs/libstdc++/manual/source_code_style.html), which actually have a lot in common with the other standard libraries. Other standard libraries would require some edits to make sure it exactly fits their naming scheme. libc++ might be the one with the most differing programming conventions, actually!


## Required Libraries for Testing and Documentation Generation in libstdc++'s repository

Testing requires graphviz, coreutils, bash and dejagnu when integrated in GNU.

Documentation requires a capable Docbook processor and a whole slew of other things.

Below is the invocation for a debian sid (testing) machine to pick up all the packages:

> `sudo apt-get install texlive-full libxslt1.1 libxml2 dblatex`
> ` docbook2x docbook5-xml docbook-xml docbook-xsl docbook-xsl-doc-pdf`
> ` docbook-xsl-doc-pdf docbook-xsl-ns docbook-utils doxygen doxygen-latex`
> ` graphviz coreutils bash dejagnu`


### Testing

There is no Catch2 for libstdc++; they use deja-gnu instead. The tests seem basic and lack hard assertions in some of them, and reading the tests makes it entirely unclear whether they are testing barebones ability to compile or actual functionality? Still, some of the tests include a file called testsuite_hooks.h, which provides a `VERIFY` macro. This is the most analogous to Catch2's `REQUIRE`; since the entirety of my tests are based on `REQUIRE` and the use of `TEMPLATE_TEST_CASE` and `SECTION` are purely organizational and sanity, I can replace all of that and essentially perform a 1-to-1 sub in of the functionality.

This might go against how tests are done in libstdc++, however: all tests are written to test a very small bit of functionality, scattered across hundreds of files... we will see how the patch goes.


### Documentation

Documentation is written with Docbook. It can be converted VIA pandoc on modern machines, but libstdc++ has style sheets and quite a bit more that attempt to provide prettier templates and some defaults. All of the conversions are done in config and makefiles in some impenetrable and inscrutable manner whose black magic and required tools are captured in the command line above. I personally am super uninterested in figuring out how the black magic actually works; I just want to write conforming docs that can be used within the system. Hence the choice of the same XML Docbook semantic markup writing.
