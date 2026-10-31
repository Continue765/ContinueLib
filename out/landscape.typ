#let latin = "TeX Gyre Termes"
#let cjk = ("FandolSong", "KaiTi")
#let mono = ("Consolas", "FandolSong")
#let ink = rgb("263442")
#let muted = rgb("747e87")
#let rule = rgb("c4cbd1")

// ---- 正文与紧凑标题 ----
#set document(title: [Algorithm Handbook], author: "Continue")
#set text(font: (latin, ..cjk), size: 9pt, lang: "zh", region: "cn")
#set par(justify: true, leading: 0.42em, first-line-indent: 0pt)
#set heading(numbering: "1.1.1")
#let hsize = (12pt, 10pt, 9pt)
#let hspace = ((8pt, 4pt), (6pt, 3pt), (5pt, 2pt))
#show heading: it => {
  let lv = calc.clamp(it.level, 1, 3)
  let (above, below) = hspace.at(lv - 1)
  block(above: above, below: below, sticky: true, {
    set text(size: hsize.at(lv - 1), weight: "bold", fill: ink)
    let title = {
      if it.numbering != none {
        numbering(it.numbering, ..counter(heading).at(it.location()))
        h(0.65em)
      }
      it.body
    }
    if lv == 1 {
      stack(spacing: 3pt, title, line(length: 100%, stroke: 0.4pt + rule))
    } else { title }
  })
}

// ---- 代码框：外置行号，续行不重复编号，框可跨栏/跨页 ----
#let code-size = 8pt
#let number-size = 5pt
#let code-line-gap = 1.5pt    // 每个源码行额外留白，续行用 par 的行距
#let framesep = 2.5pt
#let numbersep = 4.5pt
#set raw(tab-size: 4, theme: "landscape.tmTheme")
#show raw: set text(font: mono, size: code-size)
#show raw.where(block: false): set text(1em)

#let visible-code(path) = {
  let lines = read(path).split("\n").filter(line => {
    line.trim().matches(regex("^#\\s*(include\\b|pragma\\s+once\\b)")).len() == 0
  })
  while lines.len() > 0 and lines.first().trim() == "" {
    lines = lines.slice(1)
  }
  while lines.len() > 0 and lines.last().trim() == "" {
    lines = lines.slice(0, -1)
  }
  lines.join("\n")
}
#let code(path) = {
  let src = visible-code(path)
  let numw = measure(text(font: mono, size: number-size,
    str(src.matches("\n").len() + 1))).width
  block(
    width: 100%,
    outset: (x: framesep),
    inset: (x: 0pt, y: 3pt),
    stroke: 0.25pt + rule,
    above: 3pt, below: 5pt,
    breakable: true,
    {
      show raw.line: it => {
        set block(spacing: 0pt, above: 0pt, below: 0pt)
        set par(leading: 0.5em)
        pad(bottom: code-line-gap, block(inset: (left: -(numw + numbersep)), grid(
          columns: (numw, 1fr),
          column-gutter: numbersep,
          align: (right + top, left + top),
          text(size: number-size, fill: muted, baseline: 1.8pt)[#it.number],
          it.body,
        )))
      }
      raw(src, lang: "cpp", block: true)
    },
  )
}
#show raw.where(lang: "cpp-ref"): it => code("/" + it.text.trim())

// ---- 说明文件 ----
#show math.equation.where(block: true): set block(above: 6pt, below: 6pt)
#let prose(p) = block(above: 0pt, below: 0pt, {
  set par(leading: 0.48em)
  include p
})
#show raw.where(lang: "typ-prose"): it => prose("/" + it.text.trim())

// ---- 页面：底部居中页码 ----
#set page(paper: "a4", flipped: true, margin: 13mm, header: none,
  footer: context align(center, text(font: latin, size: 9pt, fill: ink,
    str(counter(page).get().first()))),
)

// ---- 左半页上部封面 → 每半页三栏目录 → 双栏正文 ----
#set page(background: align(center + top, move(dy: 13mm,
  line(angle: 90deg, length: 184mm, stroke: 0.2pt + rgb("e0e4e7")),
)))
// 目录按实际行高分栏；续半页按三栏的总高度平衡，正文紧接其后。
#let toc-part(part) = context {
  let items = query(heading).filter(h => h.numbering != none and h.level <= 3)
  let col-width = (271mm - 9mm) / 2
  let toc-width = (col-width - 6mm) / 3
  let entry(h) = pad(bottom: 5pt, block(width: 100%, above: 0pt, below: 0pt, {
    set text(size: 8.5pt, fill: if h.level == 1 { ink } else { black },
      stroke: if h.level == 1 { 0.08pt + ink } else { none },
      weight: if h.level == 1 { "black" } else { "regular" })
    set par(leading: 0.65em)
      pad(left: (h.level - 1) * 5pt, link(h.location(), grid(
      columns: (1fr, auto), column-gutter: 3pt, align: top,
      {
        numbering(h.numbering, ..counter(heading).at(h.location()))
        text(" ")
        h.body
      },
      str(counter(page).at(h.location()).first()),
    )))
  }))
  let heights = items.map(h => measure(entry(h), width: toc-width).height)
  let first-end = 0
  let used = 0pt
  let col = 0
  for i in range(items.len()) {
    let height = heights.at(i)
    if used + height > 50mm {
      col += 1
      used = 0pt
    }
    if col >= 3 { break }
    used += height
    first-end = i + 1
  }
  let toc(start, end, height) = {
    let cells = ()
    let rows = ()
    let used = 0pt
    for i in range(start, end) {
      let size = heights.at(i)
      if used + size > height and rows.len() > 0 and cells.len() < 2 {
        cells.push(stack(spacing: 0pt, ..rows))
        rows = ()
        used = 0pt
      }
      rows.push(entry(items.at(i)))
      used += size
    }
    cells.push(stack(spacing: 0pt, ..rows))
    grid(columns: (1fr, 1fr, 1fr), gutter: 3mm, ..cells)
  }
  if part == 0 {
    toc(0, first-end, 50mm)
  } else {
    let remaining = heights.slice(first-end)
    let target = remaining.fold(0pt, (a, b) => a + b) / 3 + calc.max(0pt, ..remaining)
    toc(first-end, items.len(), target)
  }
}
#columns(2, gutter: 9mm)[
    #block(height: 120mm, width: 100%)[
      #set par(justify: false)
      #v(25mm)
      #text(size: 8pt, tracking: 0.8pt, fill: muted)[CONTINUE / CODE REFERENCE]
      #v(8mm)
      #text(size: 27pt, weight: "bold", fill: ink)[Algorithm Handbook]
      #v(1fr)
      #text(size: 9pt, fill: ink)[Continue]
      #v(2pt)
      #text(size: 8pt, fill: muted)[2026 Edition]
      #v(12mm)
    ]
    #block(above: 0pt, below: 4pt)[
      #text(size: 10pt, weight: "bold", fill: ink)[Contents]
      #v(2pt)
      #line(length: 100%, stroke: 0.4pt + rule)
    ]
    #toc-part(0)
    #colbreak()
    #toc-part(1)
    #v(6pt)
    #include "body.typ"
]
