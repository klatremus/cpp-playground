
; https://stackoverflow.com/questions/4251159/set-python-indent-to-2-spaces-in-emacs-23
(add-hook 'python-mode-hook '(lambda () 
 (setq python-indent 2)))
; Hide the menu:
(tool-bar-mode -1)

; --------------------------------------------------
;; command to comment/uncomment text
(defun oboFormat-comment-dwim (arg)
  "Comment or uncomment current line or region in a smart way.
For detail, see `comment-dwim'."
  (interactive "*P")
  (require 'newcomment)
  (let (
        (comment-start "!") (comment-end "")
        )
    (comment-dwim arg)))

;; keywords for syntax coloring
(setq oboFormat-keywords
      `(
        ( ,(regexp-opt '("Sin" "Cos" "Sum") 'word) . font-lock-function-name-face)
        ( ,(regexp-opt '("Pi" "Infinity") 'word) . font-lock-constant-face)
        )
      )

;; syntax table
(defvar oboFormat-syntax-table nil "Syntax table for `oboFormat-mode'.")
(setq oboFormat-syntax-table
      (let ((synTable (make-syntax-table)))

        ;; bash style comment: “# …” 
        (modify-syntax-entry ?# "< b" synTable)
        (modify-syntax-entry ?\n "> b" synTable)

        synTable))
; --------------------------------------------------

;; define several class of keywords
(setq oboFormat-keywords '("Typedef" "Term") )
(setq oboFormat-types '("at_target" "true" "EXACT" "BROAD" "NARROW" "RELATED"))
(setq oboFormat-constants '("AGENT" "ALL_SIDES" "ATTACH_BACK"))
(setq oboFormat-events '("id" "alt_id" "name" "def" "synonym" "comment" "created_by" "creation_date" "namespace" "is_a" "inverse_of" "xref" "holds_over_chain" "intersection_of" "disjoint_from" "ontology" "format-version" "data-version" "date" "saved-by" "subsetdef" "subset" "auto-generated-by" "synonymtypedef" "treat-xrefs-as-equivalent" "remark" "default-namespace" "relationship"))
(setq oboFormat-functions '( "is_transitive" "is_transitive\d" "is_transitive[]+" "is_transitive[[]]" "is_symmetric" "is_metadata_tag" "is_anti_symmetric" "is_reflexive" "builtin relationship" "is_obsolete"  "is_cyclic" "builtin" "range" "domain"))
;(setq oboFormat-functions '( "is_transitive[:]" "is_transitive\d" "is_transitive[:]+" "is_transitive[[:]]" "is_symmetric:" "is_metadata_tag:" "is_anti_symmetric:" "is_reflexive:" "builtin relationship:" "is_obsolete:" "relationship:" "is_cyclic:" "builtin:"))

;; create the regex string for each class of keywords
(setq oboFormat-keywords-regexp (regexp-opt oboFormat-keywords 'words))
(setq oboFormat-type-regexp (regexp-opt oboFormat-types 'words))
(setq oboFormat-constant-regexp (regexp-opt oboFormat-constants 'words))
(setq oboFormat-event-regexp (regexp-opt oboFormat-events 'words))
(setq oboFormat-functions-regexp (regexp-opt oboFormat-functions 'words))

;; clear memory
(setq oboFormat-keywords nil)
(setq oboFormat-types nil)
(setq oboFormat-constants nil)
(setq oboFormat-events nil)
(setq oboFormat-functions nil)


;; create the list for font-lock.
;; each class of keyword is given a particular face
(setq oboFormat-font-lock-keywords
  `(
    (,oboFormat-type-regexp . font-lock-type-face)
    (,oboFormat-type-regexp . font-lock-doc-face)
;    (,oboFormat-type-regexp . font-lock-warning-face)
    (,oboFormat-constant-regexp . font-lock-constant-face)
    (,oboFormat-event-regexp . font-lock-builtin-face)
;    (,oboFormat-functions-regexp . font-lock-negation-char-face)
    (,oboFormat-functions-regexp . font-lock-variable-name-face)
;    (,oboFormat-functions-regexp . font-lock-function-name-face)
;    (,oboFormat-keywords-regexp . font-lock-warning-face)    
    (,oboFormat-keywords-regexp . font-lock-keyword-face)    
    ; For the regexps, see: http://ergoemacs.org/emacs/emacs_regex.html
    (, "!.*" . 'font-lock-comment-face)  ; prints the comments
;;     (, "(\([^)]+\))" . 'font-lock-warning-face) ; capture the text between paranthesis
;;     (, "::=" . 'font-lock-warning-face) 
;;     (, "<\(.*?\)>" . 'font-lock-keyword-face)  
;;     (, "<(.*?)>" . 'font-lock-function-name-face) 
;;     (, "\([^\"]+\)" . 'font-lock-function-name-face) 
;; ;    (, "<.*?>" . 'font-lock-keyword-face) 
;;     (, "<tag[^> C-q C-j ]*>\(.*?\)</tag>" . 'font-lock-keyword-face)

    ;; note: order above matters. “oboFormat-keywords-regexp” goes last because
    ;; otherwise the keyword “state” in the function “state_entry”
    ;; would be highlighted.
    ;; 
    ;; --- now an add-on to enable commenting:
;"oboFormat-mode is a major mode for editing language oboFormat." 
  :syntax-table oboFormat-syntax-table
  
  (setq font-lock-defaults '(oboFormat-keywords))
  (setq mode-name "oboFormat")
    ;; modify the keymap
  (define-key oboFormat-mode-map [remap comment-dwim] 'oboFormat-comment-dwim)
))


;; define the mode
(define-derived-mode oboFormat-mode fundamental-mode
  "obo mode"
  "Major mode for editing OBOF (OBO Format)…"
  ;; Tries adding some regexp
  ;; '("#") 
  ;; nil 
  ;; ;; '(("\[(Typedef)\]" . 'font-lock-variable-name-face) 
  ;; ;;   ("name:" . 'font-lock-keyword-face) 
  ;;    ("name:" . 'font-lock-keyword-face) 
  ;;   ("def:" . 'font-lock-keyword-face) 
;    ("::=" . 'font-lock-warning-face) 
  ;;   ("\|" . 'font-lock-warning-face))
  ;; '("\\.bnf\\.pybnf\\'") 
  ;; nil 
  ;; code for syntax highlighting
  (setq font-lock-defaults '((oboFormat-font-lock-keywords)))
  ;; '("#") 
  ;; nil 
  '(("^<.*?>" . 'font-lock-variable-name-face) 
    ("<.*?>" . 'font-lock-keyword-face) 
    ("::=" . 'font-lock-warning-face) 
    ("\|" . 'font-lock-warning-face)
    )

  ;; clear memory
;  (setq oboFormat-keywords-regexp nil)
  (setq oboFormat-types-regexp nil)
  (setq oboFormat-constants-regexp nil)
  (setq oboFormat-events-regexp nil)
  (setq oboFormat-functions-regexp nil)

)

(provide 'oboFormat-mode)

;;;###autoload
(add-to-list 'auto-mode-alist '("\\.obo\\'" . oboFormat-mode))

; --------------------------------------------------


;; ; Syntax higlightening for BNF files. (Copy-pasted from the web.) (oekseth, 25.12.2012)
;; (define-generic-mode 'obo-mode 
;;   '("#") 
;;   nil 
;;   '(("Typedef:" . 'font-lock-keyword-face) 
;;     ("name:" . 'font-lock-keyword-face) 
;;     ("name:" . 'font-lock-keyword-face) 
;;     ("def:" . 'font-lock-keyword-face) 
;;     ("::=" . 'font-lock-warning-face) 
;;     ("\|" . 'font-lock-warning-face))
;;   '("\\.bnf\\.pybnf\\'") 
;;   nil 
;;   "Major mode for BNF highlighting.")



;(require 'mercurial)

;; ===== Automatically load abbreviations table =====

;; Note that emacs chooses, by default, the filename
;; "~/.abbrev_defs", so don't try to be too clever
;; by changing its name
;(setq-default abbrev-mode t)
;(read-abbrev-file "~/.abbrev_defs")
;(setq save-abbrevs t)
(prefer-coding-system 'utf-8) 

; You need the second statement because in the MiniBuffer, `C-<tab>’ has a separate binding which overrides the global one. (http://www.emacswiki.org/emacs/DynamicAbbreviations)
;(global-set-key (kbd "C-<tab>") 'dabbrev-expand)
;(define-key minibuffer-local-map (kbd "C-<tab>") 'dabbrev-expand)
;(define-key global-set-key (kbd "C-<tab>") 'dabbrev-expand)
;(global-set-key (kbd "C-A") 'backward-char) ; Ctrl+Shift+a
;(global-set-key (kbd "C-<enter>") 'dabbrev-expand) ; http://xahlee.org/emacs/keyboard_shortcuts.html
(global-set-key (kbd "C-_") 'dabbrev-expand) ; http://xahlee.org/emacs/keyboard_shortcuts.html
;(global-set-key (kbd "C-j") 'dabbrev-expand) ; http://xahlee.org/emacs/keyboard_shortcuts.html
;(global-set-key (kbd "C-_") 'dabbrev-expand) ; http://xahlee.org/emacs/keyboard_shortcuts.html
;(global-set-key (kbd "C-æ") 'dabbrev-expand)
;(define-key global-set-key (kbd "C-æ") '(dabbrev-expand)
;; ===== Set the highlight current line minor mode =====
(global-set-key [f5] 'copy-region-as-kill) ; Copy
(global-set-key [f6] 'kill-region)         ; Cut
(global-set-key [f7] 'yank)                ; Paste 
;; In every buffer, the line which contains the cursor will be fully
;; highlighted
;(global-hl-line-mode 1)

;; ========== Support Wheel Mouse Scrolling ==========

;; ========== Support Wheel Mouse Scrolling ==========

(mouse-wheel-mode t) 

;turn on Auto Fill mode when entering Text mode and other modes based on Text mode:
;(add-hook 'text-mode-hook 'turn-on-auto-fill) ; Note: this causses a line-break in the file


					; *******************************************
					; *******************************************

;; C++ and C mode...(http://www.freebsd.org/doc/en/books/developers-handbook/emacs.html)
(defun my-c++-mode-hook ()
;  (setq tab-width 4)
;  (define-key c++-mode-map "\C-m" 'reindent-then-newline-and-indent)
;  (define-key c++-mode-map "\C-ce" 'c-comment-edit)
 ; (setq c++-auto-hungry-initial-state 'none)
;  (setq c++-delete-function 'backward-delete-char)
 ; (setq c++-tab-always-indent t)
;  (setq c-indent-level 4)
;  (setq c-continued-statement-offset 4)
 ; (setq c++-empty-arglist-indent 4)
  (define-key (kbd "C-.") 'dabbrev-expand) ; http://xahlee.org/emacs/keyboard_shortcuts.html
;  (define-key (kbd "C--") 'dabbrev-expand) ; http://xahlee.org/emacs/keyboard_shortcuts.html
					;(global-set-key (kbd "C-_") 'dabbrev-expand) ; http://xahlee.org/emacs/keyboard_shortcuts.html
;  c++-mode-map
  )

;(setq my-c-style
;      '((c-comment-only-line-offset . 4)
;	(c-cleanup-list . (scope-operator
;			   empty-defun-braces
;			   defun-close-semi))
;         (c-offsets-alist . ((arglist-close . c-lineup-arglist)
;			     (substatement-open . 0)))))

;(add-hook 'c-mode-common-hook
 ;      '(lambda ()
;          (c-add-style "my-style" my-c-style t)))

; TODO: Code below to be tested.
;; Map some keys to find-function/find-variable
;; Use C-x F to find function, C-x V to find variable
(define-key ctl-x-map "F" 'find-function)
(define-key ctl-x-map "V" 'find-variable)

; then hitting F2 will give you the man page for the library call at the current cursor position.
(global-set-key [(f2)] (lambda () (interactive) (manual-entry (current-word))))

;; Rebind C-z to start a shell (use .emacs_shellname for the shells rc file)
;(global-set-key "\C-z" 'shell)

; Function for valgrind, found at http://www.mostlymaths.net/2010/02/debugging-with-emacsvalgrind.html
; (kbd "S-")  implies shifted-return
(defun valgrind ()
  (interactive)
  (compilation-minor-mode)
  (define-key compilation-minor-mode-map (kbd "")'comint-send-input)
  (define-key compilation-minor-mode-map (kbd "S-")'compile-goto-error)
)

(add-hook 'shell-mode-hook 'valgrind)

;; (autoload 'matlab-mode "/home/klatremus/Dokumenter/emacs/matlab.el" "Enter Matlab mode." t)
;; (setq auto-mode-alist (cons '("\\.m\\'" . matlab-mode) auto-mode-alist))
;; (autoload 'matlab-shell "/home/klatremus/Dokumenter/emacs/matlab.el" "Interactive Matlab mode." t) 

; Syntax higlightening for perl test-files. (oekseth, 25.12.2012)
; (autoload 'semantic-bnf-mode "semantic-bnf" "Mode for Bovine Normal Form." t)
;(add-to-list 'auto-mode-alist '("\\.bnf$" . semantic-bnf-mode))
(add-to-list 'auto-mode-alist '("\\.t$" . perl-mode))
(add-to-list 'auto-mode-alist '("\\.ts$" . js-mode))
(add-to-list 'auto-mode-alist '("\\.tsx$" . js-mode))

; Syntax higlightening for BNF files. (Copy-pasted from the web.) (oekseth, 25.12.2012)
(define-generic-mode 'obo-mode 
  '("#") 
  nil 
  '(("\[(Typedef)\]" . 'font-lock-variable-name-face) 
    ("name:" . 'font-lock-keyword-face) 
    ("name:" . 'font-lock-keyword-face) 
    ("def:" . 'font-lock-keyword-face) 
    ("::=" . 'font-lock-warning-face) 
    ("\|" . 'font-lock-warning-face))
  '("\\.bnf\\.pybnf\\'") 
  nil 
  "Major mode for BNF highlighting.")


; Syntax higlightening for BNF files. (Copy-pasted from the web.) (oekseth, 25.12.2012)
(define-generic-mode 'bnf-mode 
  '("#") 
  nil 
  '(("^<.*?>" . 'font-lock-variable-name-face) 
    ("<.*?>" . 'font-lock-keyword-face) 
    ("::=" . 'font-lock-warning-face) 
    ("\|" . 'font-lock-warning-face))
  '("\\.bnf\\.pybnf\\'") 
  nil 
  "Major mode for BNF highlighting.")

;; Compilation output
;(setq compilation-scroll-output t)
;; Comment-region equal to "c-mode"
 ;; (eval-after-load "perl-mode"
 ;;    '(define-key perl-mode-map "\C-c\C-c"  'comment-region))


;; (defun uncomment-region (beg end &optional arg)
;;    (interactive "*r\np")
;;    (comment-region beg end (- arg)))
(global-set-key "\C-c\C-c" 'comment-region)
(global-set-key "\C-c\C-z" 'uncomment-region)
(put 'upcase-region 'disabled nil)

(setq ispell-really-hunspell t)

;; Compilation output
;(setq compilation-scroll-output t)
;; Comment-region equal to "c-mode"
 ;; (eval-after-load "perl-mode"
 ;;    '(define-key perl-mode-map "\C-c\C-c"  'comment-region))


;; (defun uncomment-region (beg end &optional arg)
;;    (interactive "*r\np")
;;    (comment-region beg end (- arg)))
(global-set-key "\C-c\C-c" 'comment-region)
(global-set-key "\C-c\C-z" 'uncomment-region)
(put 'upcase-region 'disabled nil)

(setq ispell-really-hunspell t)

; ------------- load files
; (load "~/.emacs.d/frame-fns.el") ; for frames
; (load "~/.emacs.d/frame-cmds.el") ; for frames

; load-file ("~/.emacs.d/xyz-mode.el") 
(put 'downcase-region 'disabled nil)

(add-to-list 'load-path "/home/klatremus/bin/ESS/lisp/")
(load "ess-site")
;(require 'ess-site) ; used for R-language-support (oekseth, 06. jan. 2017)
