window.addEventListener('load', function () {
    $('pre > code').each(function (_, element) {
        $(element).parent().wrap('<div style="position: relative;"></div>');
        $(element).parent().parent().append('<button type="button" class="code-btn code-copy-btn" title="Copied!">Copy</button>');
    });
    $('.code-copy-btn').on('click', function () {
        const code = $(this).siblings(':first')[0];
        window.getSelection().selectAllChildren(code);
        document.execCommand('copy');
        window.getSelection().removeAllRanges();
        $(this).showBalloon();
        const button = this;
        setTimeout(function () { $(button).hideBalloon(); }, 300);
    });
});
