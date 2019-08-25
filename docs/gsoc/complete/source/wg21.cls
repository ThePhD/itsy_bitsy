\ProvidesClass{wg21}[2016/09/11 version 0.0.1 A class for writing C++ proposals]
\NeedsTeXFormat{LaTeX2e}

\LoadClass[11pt]{article}

\RequirePackage[american]{babel}        % needed for iso dates
\RequirePackage[iso,american]{isodate}  % use iso format for dates
\RequirePackage[final]{listings}        % code listings
\RequirePackage{longtable}              % auto-breaking tables
\RequirePackage{ltcaption}              % fix captions for long tables
\RequirePackage{booktabs}               % fancy tables
\RequirePackage{relsize}                % provide relative font size changes
\RequirePackage{textcomp}               % provide \text{l,r}angle
\RequirePackage{underscore}             % remove special status of '_' in ordinary text
\RequirePackage{verbatim}               % improved verbatim environment
\RequirePackage{parskip}                % handle non-indented paragraphs "properly"
\RequirePackage{array}                  % new column definitions for tables
\RequirePackage[normalem]{ulem}
\RequirePackage{color}                  % define colors for strikeouts and underlines
\RequirePackage{amsmath}                % additional math symbols
\RequirePackage{mathrsfs}               % mathscr font
\RequirePackage{etoolbox}
\RequirePackage{microtype}
\RequirePackage{multicol}
\RequirePackage{xspace}
\RequirePackage{fullpage}
\RequirePackage{fixme}
\RequirePackage{lmodern}
\RequirePackage[T1]{fontenc}
\RequirePackage[pdftex, final]{graphicx}
\RequirePackage[pdftex,
                bookmarks=true,
                bookmarksnumbered=true,
                pdfpagelabels=true,
                pdfpagemode=UseOutlines,
                pdfstartview=FitH,
                linktocpage=true,
                colorlinks=true,
                linkcolor=blue,
                allcolors=blue,
                plainpages=false
               ]{hyperref}
\RequirePackage[active,
                header=false,
                handles=false,
                copydocumentclass=false,
                generate=std-gram.ext,
                extract-cmdline={gramSec},
                extract-env={bnftab,simplebnf,bnf,bnfkeywordtab}
               ]{extract} % Grammar extraction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Setup title
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% defines the title of the paper
% usage: \title{<title>}
\renewcommand*{\title}[1]{\def\@title{#1}}

% defines the paper number
% usage: \docnumber{<document-number>}
\newcommand*{\docnumber}[1]{\def\@docnumber{#1}}

% defines the audience working group
% usage: \audience{<audience>}
\newcommand*{\audience}[1]{\def\@audience{#1}}

% Defines the author of the paper and their email address.
% usage: \author{<author>}{<email>}
\renewcommand*{\author}[3]{\def\@author{#1} \def\@email{#2} \def\@institution{#3}}
\newcommand*{\authortwo}[2]{\def\@authortwo{#1} \def\@emailtwo{#2}}
\newcommand*{\authorthree}[2]{\def\@authorthree{#1} \def\@emailthree{#2}}
\newcommand*{\authorfour}[2]{\def\@authorfour{#1} \def\@emailfour{#2}}


\renewcommand{\maketitle}{%
  \null \vskip 1em%
  {\center \LARGE \@title \par}%
  \begin{center}%
    \begin{tabular}{ll}%
      Date:       &\today\\%
      Project:    &libstdc++, Programming Language C++\\%
      Audience:   &\@audience\\%
      Reply-to:   &\@author \textless\href{mailto:\@email}{\@email}\textgreater\\&\@institution%
                  \ifdef{\@authortwo}{\\&\@authortwo\ \textless\href{mailto:\@emailtwo}{\@emailtwo}\textgreater}{}%
                  \ifdef{\@authorthree}{\\&\@authorthree\ \textless\href{mailto:\@emailthree}{\@emailthree}\textgreater}{}%
                  \ifdef{\@authorfour}{\\&\@authorfour\ \textless\href{mailto:\@emailfour}{\@emailfour}\textgreater}{}%
    \end{tabular}%
  \end{center}%
}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Miscellaneous stuff done in the C++ standard draft; don't want to remove
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\renewcommand\RSsmallest{5.5pt}  % smallest font size for relsize

% fix interaction between hyperref and other commands
\pdfstringdefDisableCommands{\def\smaller#1{#1}}
\pdfstringdefDisableCommands{\def\textbf#1{#1}}
\pdfstringdefDisableCommands{\def\raisebox#1{}}
\pdfstringdefDisableCommands{\def\hspace#1{}}

% add special hyphenation rules
\hyphenation{tem-plate ex-am-ple in-put-it-er-a-tor name-space name-spaces}

% turn off all ligatures inside \texttt
\DisableLigatures{encoding = T1, family = tt*}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Macros defined in the C++ standard draft
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%--------------------------------------------------
%% Difference markups
\definecolor{addclr}{rgb}{0,.39,0}
\definecolor{remclr}{rgb}{1,0,0}
\definecolor{noteclr}{rgb}{0,0,1}

\newcommand{\added}[1]{\textcolor{addclr}{\uline{#1}}}
\newcommand{\removed}[1]{\textcolor{remclr}{\sout{#1}}}
\newcommand{\changed}[2]{\removed{#1} \added{#2}}

\newenvironment{addedm}{\color{addclr}}{ }
\newenvironment{changedm}{\color{noteclr}}{ }
\newenvironment{removedm}{\color{remclr}}{ }

\newcommand{\nbc}[1]{[#1]\ }
\newcommand{\addednb}[2]{\added{\nbc{#1}#2}}
\newcommand{\removednb}[2]{\removed{\nbc{#1}#2}}
\newcommand{\changednb}[3]{\removednb{#1}{#2}\added{#3}}
\newcommand{\remitem}[1]{\item\removed{#1}}

\newcommand{\ednote}[1]{\textcolor{noteclr}{[Editor's note: #1] }}

\newenvironment{addedblock}
{
\color{addclr}
}
{
\color{black}
}
\newenvironment{removedblock}
{
\color{remclr}
}
{
\color{black}
}

%%--------------------------------------------------
%% Grammar extraction.
\def\gramSec[#1]#2{}

\makeatletter
\newcommand{\FlushAndPrintGrammar}{%
\immediate\closeout\XTR@out%
\immediate\openout\XTR@out=std-gram-dummy.tmp%
\def\gramSec[##1]##2{\rSec1[##1]{##2}}%
\input{std-gram.ext}%
}
\makeatother

%%--------------------------------------------------
%% Cross references.
\newcommand{\addxref}[1]{\glossary[xrefindex]{#1}{(\ref{#1})}}

%%--------------------------------------------------
%% Sectioning macros.
% Each section has a depth, an automatically generated section
% number, a name, and a short tag.  The depth is an integer in
% the range [0,5].  (If it proves necessary, it wouldn't take much
% programming to raise the limit from 5 to something larger.)


% The basic sectioning command.  Example:
%    \Sec1[intro.scope]{Scope}
% defines a first-level section whose name is "Scope" and whose short
% tag is intro.scope.  The square brackets are mandatory.
\def\Sec#1[#2]#3{%
\ifcase#1\let\s=\chapter
      \or\let\s=\section
      \or\let\s=\subsection
      \or\let\s=\subsubsection
      \or\let\s=\paragraph
      \or\let\s=\subparagraph
      \fi%
\s[#3]{#3\hfill[#2]}\label{#2}\addxref{#2}}

% A convenience feature (mostly for the convenience of the Project
% Editor, to make it easy to move around large blocks of text):
% the \rSec macro is just like the \Sec macro, except that depths
% relative to a global variable, SectionDepthBase.  So, for example,
% if SectionDepthBase is 1,
%   \rSec1[temp.arg.type]{Template type arguments}
% is equivalent to
%   \Sec2[temp.arg.type]{Template type arguments}
\newcounter{SectionDepthBase}
\newcounter{scratch}

\def\rSec#1[#2]#3{%
\setcounter{scratch}{#1}
\addtocounter{scratch}{\value{SectionDepthBase}}
\Sec{\arabic{scratch}}[#2]{#3}}

\newcommand{\synopsis}[1]{\textbf{#1}}

%%--------------------------------------------------
% Indexing

% locations
\newcommand{\indextext}[1]{\index[generalindex]{#1}}
\newcommand{\indexlibrary}[1]{\index[libraryindex]{#1}}
\newcommand{\indexgram}[1]{\index[grammarindex]{#1}}
\newcommand{\indeximpldef}[1]{\index[impldefindex]{#1}}

\newcommand{\indexdefn}[1]{\indextext{#1}}
\newcommand{\indexgrammar}[1]{\indextext{#1}\indexgram{#1}}
\newcommand{\impldef}[1]{\indeximpldef{#1}implementation-defined}

% appearance
\newcommand{\idxcode}[1]{#1@\tcode{#1}}
\newcommand{\idxhdr}[1]{#1@\tcode{<#1>}}
\newcommand{\idxgram}[1]{#1@\textit{#1}}

%%--------------------------------------------------
% General code style
\newcommand{\CodeStyle}{\ttfamily}
\newcommand{\CodeStylex}[1]{\texttt{#1}}

% Code and definitions embedded in text.
\newcommand{\tcode}[1]{\CodeStylex{#1}}
\newcommand{\techterm}[1]{\textit{#1}\xspace}
\newcommand{\defnx}[2]{\indexdefn{#2}\textit{#1}\xspace}
\newcommand{\defn}[1]{\defnx{#1}{#1}}
\newcommand{\term}[1]{\textit{#1}\xspace}
\newcommand{\grammarterm}[1]{\textit{#1}\xspace}
\newcommand{\placeholder}[1]{\textit{#1}}
\newcommand{\placeholdernc}[1]{\textit{#1\nocorr}}

%%--------------------------------------------------
%% allow line break if needed for justification
\newcommand{\brk}{\discretionary{}{}{}}
%  especially for scope qualifier
\newcommand{\colcol}{\brk::\brk}

%%--------------------------------------------------
%% Macros for funky text
\newcommand{\Cpp}{\texorpdfstring{C\kern-0.05em\protect\raisebox{.35ex}{\textsmaller[2]{+\kern-0.05em+}}}{C++}\xspace}
\newcommand{\CppIII}{\Cpp 2003\xspace}
\newcommand{\CppXI}{\Cpp 2011\xspace}
\newcommand{\CppXIV}{\Cpp 2014\xspace}
\newcommand{\opt}{{\ensuremath{_\mathit{opt}}}\xspace}
\newcommand{\shl}{<{<}}
\newcommand{\shr}{>{>}}
\newcommand{\dcr}{-{-}}
\newcommand{\exor}{\^{}}
\newcommand{\bigoh}[1]{\ensuremath{\mathscr{O}(#1)}}

% Make all tildes a little larger to avoid visual similarity with hyphens.
% FIXME: Remove \tilde in favour of \~.
\renewcommand{\tilde}{\textasciitilde}
\renewcommand{\~}{\textasciitilde}
\let\OldTextAsciiTilde\textasciitilde
\renewcommand{\textasciitilde}{\protect\raisebox{-0.17ex}{\larger\OldTextAsciiTilde}}

%%--------------------------------------------------
%% States and operators
\newcommand{\state}[2]{\tcode{#1}\ensuremath{_{#2}}}
\newcommand{\bitand}{\ensuremath{\, \mathsf{bitand} \,}}
\newcommand{\bitor}{\ensuremath{\, \mathsf{bitor} \,}}
\newcommand{\xor}{\ensuremath{\, \mathsf{xor} \,}}
\newcommand{\rightshift}{\ensuremath{\, \mathsf{rshift} \,}}
\newcommand{\leftshift}[1]{\ensuremath{\, \mathsf{lshift}_#1 \,}}

%% Notes and examples
\newcommand{\noteintro}[1]{[\,\textit{#1:}\space}
\newcommand{\noteoutro}[1]{\textit{\,---\,end #1}\,]}
\newenvironment{note}[1][Note]{\noteintro{#1}}{\noteoutro{note}\xspace}
\newenvironment{example}[1][Example]{\noteintro{#1}}{\noteoutro{example}\xspace}

%% Library function descriptions
\newcommand{\Fundescx}[1]{\textit{#1}\xspace}
\newcommand{\Fundesc}[1]{\Fundescx{#1:}}
\newcommand{\required}{\Fundesc{Required behavior}}
\newcommand{\requires}{\Fundesc{Requires}}
\newcommand{\effects}{\Fundesc{Effects}}
\newcommand{\postconditions}{\Fundesc{Postconditions}}
\newcommand{\postcondition}{\Fundesc{Postcondition}}
\newcommand{\preconditions}{\requires}
\newcommand{\precondition}{\requires}
\newcommand{\returns}{\Fundesc{Returns}}
\newcommand{\throws}{\Fundesc{Throws}}
\newcommand{\default}{\Fundesc{Default behavior}}
\newcommand{\complexity}{\Fundesc{Complexity}}
\newcommand{\remark}{\Fundesc{Remark}}
\newcommand{\remarks}{\Fundesc{Remarks}}
\newcommand{\realnote}{\Fundesc{Note}}
\newcommand{\realnotes}{\Fundesc{Notes}}
\newcommand{\errors}{\Fundesc{Error conditions}}
\newcommand{\sync}{\Fundesc{Synchronization}}
\newcommand{\implimits}{\Fundesc{Implementation limits}}
\newcommand{\replaceable}{\Fundesc{Replaceable}}
\newcommand{\returntype}{\Fundesc{Return type}}
\newcommand{\cvalue}{\Fundesc{Value}}
\newcommand{\ctype}{\Fundesc{Type}}
\newcommand{\ctypes}{\Fundesc{Types}}
\newcommand{\dtype}{\Fundesc{Default type}}
\newcommand{\ctemplate}{\Fundesc{Class template}}
\newcommand{\templalias}{\Fundesc{Alias template}}

%% Cross reference
\newcommand{\xref}{\textsc{See also:}\xspace}
\newcommand{\xsee}{\textsc{See:}\xspace}

%% NTBS, etc.
\newcommand{\NTS}[1]{\textsc{#1}\xspace}
\newcommand{\ntbs}{\NTS{ntbs}}
\newcommand{\ntmbs}{\NTS{ntmbs}}
\newcommand{\ntwcs}{\NTS{ntwcs}}
\newcommand{\ntcxvis}{\NTS{ntc16s}}
\newcommand{\ntcxxxiis}{\NTS{ntc32s}}

%% Code annotations
\newcommand{\EXPO}[1]{\textit{#1}}
\newcommand{\expos}{\EXPO{exposition only}}
\newcommand{\impdef}{\EXPO{implementation-defined}}
\newcommand{\impdefnc}{\EXPO{implementation-defined\nocorr}}
\newcommand{\impdefx}[1]{\indeximpldef{#1}\EXPO{implementation-defined}}
\newcommand{\notdef}{\EXPO{not defined}}

\newcommand{\UNSP}[1]{\textit{\texttt{#1}}}
\newcommand{\UNSPnc}[1]{\textit{\texttt{#1}\nocorr}}
\newcommand{\unspec}{\UNSP{unspecified}}
\newcommand{\unspecnc}{\UNSPnc{unspecified}}
\newcommand{\unspecbool}{\UNSP{unspecified-bool-type}}
\newcommand{\seebelow}{\UNSP{see below}}
\newcommand{\seebelownc}{\UNSPnc{see below}}
\newcommand{\unspecuniqtype}{\UNSP{unspecified unique type}}
\newcommand{\unspecalloctype}{\UNSP{unspecified allocator type}}

\newcommand{\EXPLICIT}{\textit{\texttt{EXPLICIT}}}

%% Manual insertion of italic corrections, for aligning in the presence
%% of the above annotations.
\newlength{\itcorrwidth}
\newlength{\itletterwidth}
\newcommand{\itcorr}[1][]{%
 \settowidth{\itcorrwidth}{\textit{x\/}}%
 \settowidth{\itletterwidth}{\textit{x\nocorr}}%
 \addtolength{\itcorrwidth}{-1\itletterwidth}%
 \makebox[#1\itcorrwidth]{}%
}

%% Double underscore
\newcommand{\ungap}{\kern.5pt}
\newcommand{\unun}{\textunderscore\ungap\textunderscore}
\newcommand{\xname}[1]{\tcode{\unun\ungap#1}}
\newcommand{\mname}[1]{\tcode{\unun\ungap#1\ungap\unun}}

%% Ranges
\newcommand{\Range}[4]{\tcode{#1#3,~\brk{}#4#2}\xspace}
\newcommand{\crange}[2]{\Range{[}{]}{#1}{#2}}
\newcommand{\brange}[2]{\Range{(}{]}{#1}{#2}}
\newcommand{\orange}[2]{\Range{(}{)}{#1}{#2}}
\newcommand{\range}[2]{\Range{[}{)}{#1}{#2}}

%% Change descriptions
\newcommand{\diffdef}[1]{\hfill\break\textbf{#1:}\xspace}
\newcommand{\change}{\diffdef{Change}}
\newcommand{\rationale}{\diffdef{Rationale}}
\newcommand{\effect}{\diffdef{Effect on original feature}}
\newcommand{\difficulty}{\diffdef{Difficulty of converting}}
\newcommand{\howwide}{\diffdef{How widely used}}

%% Miscellaneous
\newcommand{\uniquens}{\textrm{\textit{\textbf{unique}}}}
\newcommand{\stage}[1]{\item{\textbf{Stage #1:}}\xspace}
\newcommand{\doccite}[1]{\textit{#1}\xspace}
\newcommand{\cvqual}[1]{\textit{#1}}
\newcommand{\cv}{\cvqual{cv}}
\renewcommand{\emph}[1]{\textit{#1}\xspace}
\newcommand{\numconst}[1]{\textsl{#1}\xspace}
\newcommand{\logop}[1]{{\footnotesize #1}\xspace}

%%--------------------------------------------------
%% Environments for code listings.

% We use the 'listings' package, with some small customizations.  The
% most interesting customization: all TeX commands are available
% within comments.  Comments are set in italics, keywords and strings
% don't get special treatment.

\lstset{language=C++,
        basicstyle=\small\CodeStyle,
        keywordstyle=,
        stringstyle=,
        xleftmargin=0em,
        showstringspaces=false,
        commentstyle=\itshape\rmfamily,
        columns=flexible,
        keepspaces=true,
        texcl=true}

% Our usual abbreviation for 'listings'.  Comments are in
% italics.  Arbitrary TeX commands can be used if they're
% surrounded by @ signs.
\newcommand{\CodeBlockSetup}{
 \lstset{escapechar=@}
 \renewcommand{\tcode}[1]{\textup{\CodeStylex{##1}}}
 \renewcommand{\techterm}[1]{\textit{\CodeStylex{##1}}}
 \renewcommand{\term}[1]{\textit{##1}}
 \renewcommand{\grammarterm}[1]{\textit{##1}}
}

\lstnewenvironment{codeblock}{\CodeBlockSetup}{}

% A code block in which single-quotes are digit separators
% rather than character literals.
\lstnewenvironment{codeblockdigitsep}{
 \CodeBlockSetup
 \lstset{deletestring=[b]{'}}
}{}

% Permit use of '@' inside codeblock blocks (don't ask)
\makeatletter
\newcommand{\atsign}{@}
\makeatother

%%--------------------------------------------------
%% Indented text
\newenvironment{indented}
{\list{}{}\item\relax}
{\endlist}

%%--------------------------------------------------
%% Library item descriptions
\lstnewenvironment{itemdecl}
{
 \lstset{escapechar=@,
 xleftmargin=0em,
 aboveskip=2ex,
 belowskip=0ex  % leave this alone: it keeps these things out of the
        % footnote area
 }
}
{
}

\newenvironment{itemdescr}
{
 \begin{indented}}
{
 \end{indented}
}


%%--------------------------------------------------
%% Bnf environments
\newlength{\BnfIndent}
\setlength{\BnfIndent}{\leftmargini}
\newlength{\BnfInc}
\setlength{\BnfInc}{\BnfIndent}
\newlength{\BnfRest}
\setlength{\BnfRest}{2\BnfIndent}
\newcommand{\BnfNontermshape}{\small\rmfamily\itshape}
\newcommand{\BnfTermshape}{\small\ttfamily\upshape}
\newcommand{\nonterminal}[1]{{\BnfNontermshape #1}}

\newenvironment{bnfbase}
 {
 \newcommand{\nontermdef}[1]{\nonterminal{##1}\indexgrammar{\idxgram{##1}}:}
 \newcommand{\terminal}[1]{{\BnfTermshape ##1}\xspace}
 \newcommand{\descr}[1]{\normalfont{##1}}
 \newcommand{\bnfindentfirst}{\BnfIndent}
 \newcommand{\bnfindentinc}{\BnfInc}
 \newcommand{\bnfindentrest}{\BnfRest}
 \begin{minipage}{.9\hsize}
 \newcommand{\br}{\hfill\\}
 \frenchspacing
 }
 {
 \nonfrenchspacing
 \end{minipage}
 }

\newenvironment{BnfTabBase}[1]
{
 \begin{bnfbase}
 #1
 \begin{indented}
 \begin{tabbing}
 \hspace*{\bnfindentfirst}\=\hspace{\bnfindentinc}\=\hspace{.6in}\=\hspace{.6in}\=\hspace{.6in}\=\hspace{.6in}\=\hspace{.6in}\=\hspace{.6in}\=\hspace{.6in}\=\hspace{.6in}\=\hspace{.6in}\=\hspace{.6in}\=\kill}
{
 \end{tabbing}
 \end{indented}
 \end{bnfbase}
}

\newenvironment{bnfkeywordtab}
{
 \begin{BnfTabBase}{\BnfTermshape}
}
{
 \end{BnfTabBase}
}

\newenvironment{bnftab}
{
 \begin{BnfTabBase}{\BnfNontermshape}
}
{
 \end{BnfTabBase}
}

\newenvironment{simplebnf}
{
 \begin{bnfbase}
 \BnfNontermshape
 \begin{indented}
}
{
 \end{indented}
 \end{bnfbase}
}

\newenvironment{bnf}
{
 \begin{bnfbase}
 \list{}
  {
  \setlength{\leftmargin}{\bnfindentrest}
  \setlength{\listparindent}{-\bnfindentinc}
  \setlength{\itemindent}{\listparindent}
  }
 \BnfNontermshape
 \item\relax
}
{
 \endlist
 \end{bnfbase}
}

% non-copied versions of bnf environments
\let\ncbnftab\bnftab
\let\endncbnftab\endbnftab
\let\ncsimplebnf\simplebnf
\let\endncsimplebnf\endsimplebnf
\let\ncbnf\bnf
\let\endncbnf\endbnf

%%--------------------------------------------------
%% Drawing environment
%
% usage: \begin{drawing}{UNITLENGTH}{WIDTH}{HEIGHT}{CAPTION}
\newenvironment{drawing}[4]
{
\newcommand{\mycaption}{#4}
\begin{figure}[h]
\setlength{\unitlength}{#1}
\begin{center}
\begin{picture}(#2,#3)\thicklines
}
{
\end{picture}
\end{center}
\caption{\mycaption}
\end{figure}
}

%%--------------------------------------------------
%% Environment for imported graphics
% usage: \begin{importgraphic}{CAPTION}{TAG}{FILE}

\newenvironment{importgraphic}[3]
{%
\newcommand{\cptn}{#1}
\newcommand{\lbl}{#2}
\begin{figure}[htp]\centering%
\includegraphics[scale=.35]{#3}
}
{
\caption{\cptn}\label{\lbl}%
\end{figure}}

%% enumeration display overrides
% enumerate with lowercase letters
\newenvironment{enumeratea}
{
 \renewcommand{\labelenumi}{\alph{enumi})}
 \begin{enumerate}
}
{
 \end{enumerate}
}

% enumerate with arabic numbers
\newenvironment{enumeraten}
{
 \renewcommand{\labelenumi}{\arabic{enumi})}
 \begin{enumerate}
}
{
 \end{enumerate}
}

%%--------------------------------------------------
%% Definitions section
% usage: \definition{name}{xref}
%\newcommand{\definition}[2]{\rSec2[#2]{#1}}
% for ISO format, use:
\newcommand{\definition}[2]{%
\addxref{#2}%
\subsection[#1]{\hfill[#2]}\vspace{-.3\onelineskip}\label{#2}\textbf{#1}\\%
}
\newcommand{\definitionx}[2]{%
\addxref{#2}%
\subsubsection[#1]{\hfill[#2]}\vspace{-.3\onelineskip}\label{#2}\textbf{#1}\\%
}
\newcommand{\defncontext}[1]{\textlangle#1\textrangle}



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Tables
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%--------------------------------------------------
%% Table environments

% Set parameters for floating tables
\setcounter{totalnumber}{10}

% Base definitions for tables
\newenvironment{TableBase}
{
 \renewcommand{\tcode}[1]{{\CodeStylex{##1}}}
 \newcommand{\topline}{\hline}
 \newcommand{\capsep}{\hline\hline}
 \newcommand{\rowsep}{\hline}
 \newcommand{\bottomline}{\hline}

%% vertical alignment
 \newcommand{\rb}[1]{\raisebox{1.5ex}[0pt]{##1}}  % move argument up half a row

%% header helpers
 \newcommand{\hdstyle}[1]{\textbf{##1}}       % set header style
 \newcommand{\Head}[3]{\multicolumn{##1}{##2}{\hdstyle{##3}}} % add title spanning multiple columns
 \newcommand{\lhdrx}[2]{\Head{##1}{|c}{##2}}    % set header for left column spanning #1 columns
 \newcommand{\chdrx}[2]{\Head{##1}{c}{##2}}     % set header for center column spanning #1 columns
 \newcommand{\rhdrx}[2]{\Head{##1}{c|}{##2}}    % set header for right column spanning #1 columns
 \newcommand{\ohdrx}[2]{\Head{##1}{|c|}{##2}}   % set header for only column spanning #1 columns
 \newcommand{\lhdr}[1]{\lhdrx{1}{##1}}        % set header for single left column
 \newcommand{\chdr}[1]{\chdrx{1}{##1}}        % set header for single center column
 \newcommand{\rhdr}[1]{\rhdrx{1}{##1}}        % set header for single right column
 \newcommand{\ohdr}[1]{\ohdrx{1}{##1}}
 \newcommand{\br}{\hfill\break}           % force newline within table entry

%% column styles
 \newcolumntype{x}[1]{>{\raggedright\let\\=\tabularnewline}p{##1}}  % word-wrapped ragged-right
                                  % column, width specified by #1
 % \newcolumntype{m}[1]{>{\CodeStyle}l{##1}}              % variable width column, all entries in CodeStyle
 \newcolumntype{m}[1]{l{##1}}             % variable width column, all entries in CodeStyle

  % do not number bullets within tables
  \renewcommand{\labelitemi}{---}
  \renewcommand{\labelitemii}{---}
  \renewcommand{\labelitemiii}{---}
  \renewcommand{\labelitemiv}{---}
}
{
}

% General Usage: TITLE is the title of the table, XREF is the
% cross-reference for the table. LAYOUT is a sequence of column
% type specifiers (e.g. cp{1.0}c), without '|' for the left edge
% or right edge.

% usage: \begin{floattablebase}{TITLE}{XREF}{COLUMNS}{PLACEMENT}
% produces floating table, location determined within limits
% by LaTeX.
\newenvironment{floattablebase}[4]
{
 \begin{TableBase}
 \begin{table}[#4]
 \caption{\label{#2}#1}
 \begin{center}
 \begin{tabular}{|#3|}
}
{
 \bottomline
 \end{tabular}
 \end{center}
 \end{table}
 \end{TableBase}
}

% usage: \begin{floattable}{TITLE}{XREF}{COLUMNS}
% produces floating table, location determined within limits
% by LaTeX.
\newenvironment{floattable}[3]
{
 \begin{floattablebase}{#1}{#2}{#3}{htbp}
}
{
 \end{floattablebase}
}

% usage: \begin{tokentable}{TITLE}{XREF}{HDR1}{HDR2}
% produces six-column table used for lists of replacement tokens;
% the columns are in pairs -- left-hand column has header HDR1,
% right hand column has header HDR2; pairs of columns are separated
% by vertical lines. Used in the "Alternative tokens" table.
\newenvironment{tokentable}[4]
{
 \begin{floattablebase}{#1}{#2}{cc|cc|cc}{htbp}
 \topline
 #3   &   #4    &
 #3   &   #4    &
 #3   &   #4    \\ \capsep
}
{
 \end{floattablebase}
}

% usage: \begin{libsumtabbase}{TITLE}{XREF}{HDR1}{HDR2}
% produces three-column table with column headers HDR1 and HDR2.
% Used in "Library Categories" table in standard, and used as
% base for other library summary tables.
\newenvironment{libsumtabbase}[4]
{
 \begin{floattable}{#1}{#2}{lll}
 \topline
 \lhdrx{2}{#3}  & \hdstyle{#4}  \\ \capsep
}
{
 \end{floattable}
}

% usage: \begin{libsumtab}{TITLE}{XREF}
% produces three-column table with column headers "Subclause" and "Header(s)".
% Used in "C++ Headers for Freestanding Implementations" table in standard.
\newenvironment{libsumtab}[2]
{
 \begin{libsumtabbase}{#1}{#2}{Subclause}{Header(s)}
}
{
 \end{libsumtabbase}
}

% usage: \begin{LibSynTab}{CAPTION}{TITLE}{XREF}{COUNT}{LAYOUT}
% produces table with COUNT columns. Used as base for
% C library description tables
\newcounter{LibSynTabCols}
\newcounter{LibSynTabWd}
\newenvironment{LibSynTabBase}[5]
{
 \setcounter{LibSynTabCols}{#4}
 \setcounter{LibSynTabWd}{#4}
 \addtocounter{LibSynTabWd}{-1}
 \newcommand{\centry}[1]{\textbf{##1}:}
 \newcommand{\macro}{\centry{Macro}}
 \newcommand{\macros}{\centry{Macros}}
 \newcommand{\function}{\centry{Function}}
 \newcommand{\functions}{\centry{Functions}}
 \newcommand{\mfunctions}{\centry{Math Functions}}
 \newcommand{\cfunctions}{\centry{Classification/comparison Functions}}
 \newcommand{\type}{\centry{Type}}
 \newcommand{\types}{\centry{Types}}
 \newcommand{\values}{\centry{Values}}
 \newcommand{\struct}{\centry{Struct}}
 \newcommand{\cspan}[1]{\multicolumn{\value{LibSynTabCols}}{|l|}{##1}}
 \begin{floattable}{#1 \tcode{<#2>} synopsis}{#3}
 {#5}
 \topline
 \lhdr{Type}  & \rhdrx{\value{LibSynTabWd}}{Name(s)}  \\ \capsep
}
{
 \end{floattable}
}

% usage: \begin{LibSynTab}{TITLE}{XREF}{COUNT}{LAYOUT}
% produces table with COUNT columns. Used as base for description tables
% for C library
\newenvironment{LibSynTab}[4]
{
 \begin{LibSynTabBase}{Header}{#1}{#2}{#3}{#4}
}
{
 \end{LibSynTabBase}
}

% usage: \begin{LibSynTabAdd}{TITLE}{XREF}{COUNT}{LAYOUT}
% produces table with COUNT columns. Used as base for description tables
% for additions to C library
\newenvironment{LibSynTabAdd}[4]
{
 \begin{LibSynTabBase}{Additions to header}{#1}{#2}{#3}{#4}
}
{
 \end{LibSynTabBase}
}

% usage: \begin{libsyntabN}{TITLE}{XREF}
%        \begin{libsyntabaddN}{TITLE}{XREF}
% produces a table with N columns for C library description tables
\newenvironment{libsyntab2}[2]
{
 \begin{LibSynTab}{#1}{#2}{2}{ll}
}
{
 \end{LibSynTab}
}

\newenvironment{libsyntab3}[2]
{
 \begin{LibSynTab}{#1}{#2}{3}{lll}
}
{
 \end{LibSynTab}
}

\newenvironment{libsyntab4}[2]
{
 \begin{LibSynTab}{#1}{#2}{4}{llll}
}
{
 \end{LibSynTab}
}

\newenvironment{libsyntab5}[2]
{
 \begin{LibSynTab}{#1}{#2}{5}{lllll}
}
{
 \end{LibSynTab}
}

\newenvironment{libsyntab6}[2]
{
 \begin{LibSynTab}{#1}{#2}{6}{llllll}
}
{
 \end{LibSynTab}
}

\newenvironment{libsyntabadd2}[2]
{
 \begin{LibSynTabAdd}{#1}{#2}{2}{ll}
}
{
 \end{LibSynTabAdd}
}

\newenvironment{libsyntabadd3}[2]
{
 \begin{LibSynTabAdd}{#1}{#2}{3}{lll}
}
{
 \end{LibSynTabAdd}
}

\newenvironment{libsyntabadd4}[2]
{
 \begin{LibSynTabAdd}{#1}{#2}{4}{llll}
}
{
 \end{LibSynTabAdd}
}

\newenvironment{libsyntabadd5}[2]
{
 \begin{LibSynTabAdd}{#1}{#2}{5}{lllll}
}
{
 \end{LibSynTabAdd}
}

\newenvironment{libsyntabadd6}[2]
{
 \begin{LibSynTabAdd}{#1}{#2}{6}{llllll}
}
{
 \end{LibSynTabAdd}
}

% usage: \begin{libsyntabfN}{TITLE}{XREF}
% produces a fixed width table with N columns for C library description tables
\newenvironment{libsyntabf2}[2]
{
 \begin{LibSynTab}{#1}{#2}{2}{p{1in}p{4in}}
}
{
 \end{LibSynTab}
}

\newenvironment{libsyntabf3}[2]
{
 \begin{LibSynTab}{#1}{#2}{3}{p{1in}p{.9in}p{2.9in}}
}
{
 \end{LibSynTab}
}

\newenvironment{libsyntabf5}[2]
{
 \begin{LibSynTab}{#1}{#2}{5}{p{.9in}p{.9in}p{.9in}p{.9in}p{.9in}}
}
{
 \end{LibSynTab}
}

\newenvironment{libsyntabf4}[2]
{
 \begin{LibSynTab}{#1}{#2}{4}{p{1in}p{.9in}p{.9in}p{1.8in}}
}
{
 \end{LibSynTab}
}

% usage: \begin{concepttable}{TITLE}{TAG}{LAYOUT}
% produces table at current location
\newenvironment{concepttable}[3]
{
 \begin{TableBase}
 \begin{table}[!htb]
 \caption[#1]{\label{tab:#2}#1 \textbf{[#2]}}
 \begin{center}
 \begin{tabular}{|#3|}
}
{
 \bottomline
 \end{tabular}
 \end{center}
 \end{table}
 \end{TableBase}
}

% usage: \begin{simpletypetable}{TITLE}{TAG}{LAYOUT}
% produces table at current location
\newenvironment{simpletypetable}[3]
{
 \begin{TableBase}
 \begin{table}[!htb]
 \caption{#1}\label{#2}
 \begin{center}
 \begin{tabular}{|#3|}
}
{
 \bottomline
 \end{tabular}
 \end{center}
 \end{table}
 \end{TableBase}
}

% usage: \begin{LongTable}{TITLE}{XREF}{LAYOUT}
% produces table that handles page breaks sensibly.
\newenvironment{LongTable}[3]
{
 \newcommand{\continuedcaption}{\caption[]{#1 (continued)}}
 \begin{TableBase}
 \begin{longtable}
 {|#3|}\caption{#1}\label{#2}
}
{
 \bottomline
 \end{longtable}
 \end{TableBase}
}

% usage: \begin{twocol}{TITLE}{XREF}
% produces a two-column breakable table. Used in
% "simple-type-specifiers and the types they specify" in the standard.
\newenvironment{twocol}[2]
{
 \begin{concepttable}
 {#1}{#2}
 {ll}
}
{
 \end{LongTable}
}

% usage: \begin{libreqtabN}{TITLE}{XREF}
% produces an N-column breakable table. Used in
% most of the library Clauses for requirements tables.
% Example at "Position type requirements" in the standard.

\newenvironment{libreqtab1}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.55\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab2}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {lx{.55\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab2a}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.30\hsize}x{.68\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab3}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.28\hsize}x{.18\hsize}x{.43\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab3a}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.28\hsize}x{.33\hsize}x{.29\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab3b}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.40\hsize}x{.25\hsize}x{.25\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab3c}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.30\hsize}x{.25\hsize}x{.35\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab3d}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.32\hsize}x{.27\hsize}x{.36\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab3e}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.38\hsize}x{.27\hsize}x{.25\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab3f}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.35\hsize}x{.28\hsize}x{.30\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab4}[2]
{
 \begin{LongTable}
 {#1}{#2}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab4a}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.14\hsize}x{.30\hsize}x{.30\hsize}x{.14\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab4b}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.13\hsize}x{.15\hsize}x{.29\hsize}x{.27\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab4c}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.16\hsize}x{.21\hsize}x{.21\hsize}x{.30\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab4d}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.22\hsize}x{.22\hsize}x{.30\hsize}x{.15\hsize}}
}
{
 \end{LongTable}
}

\newenvironment{libreqtab5}[2]
{
 \begin{LongTable}
 {#1}{#2}
 {x{.14\hsize}x{.14\hsize}x{.20\hsize}x{.20\hsize}x{.14\hsize}}
}
{
 \end{LongTable}
}

% usage: \begin{libtab2}{TITLE}{XREF}{LAYOUT}{HDR1}{HDR2}
% produces two-column table with column headers HDR1 and HDR2.
% Used in "seekoff positioning" in the standard.
\newenvironment{libtab2}[5]
{
 \begin{floattable}
 {#1}{#2}{#3}
 \topline
 \lhdr{#4}  & \rhdr{#5} \\ \capsep
}
{
 \end{floattable}
}

% usage: \begin{longlibtab2}{TITLE}{XREF}{LAYOUT}{HDR1}{HDR2}
% produces two-column table with column headers HDR1 and HDR2.
\newenvironment{longlibtab2}[5]
{
 \begin{LongTable}{#1}{#2}{#3}
 \\ \topline
 \lhdr{#4}  & \rhdr{#5} \\ \capsep
 \endfirsthead
 \continuedcaption\\
 \topline
 \lhdr{#4}  & \rhdr{#5} \\ \capsep
 \endhead
}
{
  \end{LongTable}
}

% usage: \begin{LibEffTab}{TITLE}{XREF}{HDR2}{WD2}
% produces a two-column table with left column header "Element"
% and right column header HDR2, right column word-wrapped with
% width specified by WD2.
\newenvironment{LibEffTab}[4]
{
 \begin{libtab2}{#1}{#2}{lp{#4}}{Element}{#3}
}
{
 \end{libtab2}
}

% Same as LibEffTab except that it uses a long table.
\newenvironment{longLibEffTab}[4]
{
 \begin{longlibtab2}{#1}{#2}{lp{#4}}{Element}{#3}
}
{
 \end{longlibtab2}
}

% usage: \begin{libefftab}{TITLE}{XREF}
% produces a two-column effects table with right column
% header "Effect(s) if set", width 4.5 in. Used in "fmtflags effects"
% table in standard.
\newenvironment{libefftab}[2]
{
 \begin{LibEffTab}{#1}{#2}{Effect(s) if set}{4.5in}
}
{
 \end{LibEffTab}
}

% Same as libefftab except that it uses a long table.
\newenvironment{longlibefftab}[2]
{
 \begin{longLibEffTab}{#1}{#2}{Effect(s) if set}{4.5in}
}
{
 \end{longLibEffTab}
}

% usage: \begin{libefftabmean}{TITLE}{XREF}
% produces a two-column effects table with right column
% header "Meaning", width 4.5 in. Used in "seekdir effects"
% table in standard.
\newenvironment{libefftabmean}[2]
{
 \begin{LibEffTab}{#1}{#2}{Meaning}{4.5in}
}
{
 \end{LibEffTab}
}

% Same as libefftabmean except that it uses a long table.
\newenvironment{longlibefftabmean}[2]
{
 \begin{longLibEffTab}{#1}{#2}{Meaning}{4.5in}
}
{
 \end{longLibEffTab}
}

% usage: \begin{libefftabvalue}{TITLE}{XREF}
% produces a two-column effects table with right column
% header "Value", width 3 in. Used in "basic_ios::init() effects"
% table in standard.
\newenvironment{libefftabvalue}[2]
{
 \begin{LibEffTab}{#1}{#2}{Value}{3in}
}
{
 \end{LibEffTab}
}

% usage: \begin{libefftabvaluenarrow}{TITLE}{XREF}
% produces a two-column effects table with right column
% header "Value", width 1.5 in. Used in basic_string_view effects
% tables in standard.
\newenvironment{libefftabvaluenarrow}[2]
{
 \begin{LibEffTab}{#1}{#2}{Value}{1.3in}
}
{
 \end{LibEffTab}
}

% Same as libefftabvalue except that it uses a long table and a
% slightly wider column.
\newenvironment{longlibefftabvalue}[2]
{
 \begin{longLibEffTab}{#1}{#2}{Value}{3.5in}
}
{
 \end{longLibEffTab}
}

% usage: \begin{liberrtab}{TITLE}{XREF} produces a two-column table
% with left column header ``Value'' and right header "Error
% condition", width 4.5 in. Used in regex Clause in the TR.

\newenvironment{liberrtab}[2]
{
 \begin{libtab2}{#1}{#2}{lp{4.5in}}{Value}{Error condition}
}
{
 \end{libtab2}
}

% Like liberrtab except that it uses a long table.
\newenvironment{longliberrtab}[2]
{
 \begin{longlibtab2}{#1}{#2}{lp{4.5in}}{Value}{Error condition}
}
{
 \end{longlibtab2}
}

% usage: \begin{lib2dtab2base}{TITLE}{XREF}{HDR1}{HDR2}{WID1}{WID2}{WID3}
% produces a table with one heading column followed by 2 data columns.
% used for 2D requirements tables, such as optional::operator= effects
% tables.
\newenvironment{lib2dtab2base}[7]
{
 %% no lines in the top-left cell, and leave a gap around the headers
 %% FIXME: I tried to use hhline here, but it doesn't appear to support
 %% the join between the leftmost top header and the topmost left header,
 %% so we fake it with an empty row and column.
 \newcommand{\topline}{\cline{3-4}}
 \newcommand{\rowsep}{\cline{1-1}\cline{3-4}}
 \newcommand{\capsep}{
  \topline
  \multicolumn{4}{c}{}\\[-0.8\normalbaselineskip]
  \rowsep
 }
 \newcommand{\bottomline}{\rowsep}
 \newcommand{\hdstyle}[1]{\textbf{##1}}
 \newcommand{\rowhdr}[1]{\hdstyle{##1}&}
 \newcommand{\colhdr}[1]{\multicolumn{1}{|>{\centering}m{#6}|}{\hdstyle{##1}}}
 %% FIXME: figure out a way to reuse floattable here
 \begin{table}[htbp]
 \caption{\label{#2}#1}
 \begin{center}
 \begin{tabular}{|>{\centering}m{#5}|@{}p{0.2\normalbaselineskip}@{}|m{#6}|m{#7}|}
 %% table header
 \topline
 \multicolumn{1}{c}{}&&\colhdr{#3}&\colhdr{#4}\\
 \capsep
}
{
 \bottomline
 \end{tabular}
 \end{center}
 \end{table}
}

\newenvironment{lib2dtab2}[4]{
 \begin{lib2dtab2base}{#1}{#2}{#3}{#4}{1.2in}{1.8in}{1.8in}
}{
 \end{lib2dtab2base}
}

\endinput
