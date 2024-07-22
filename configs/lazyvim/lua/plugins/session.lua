return {
  "rmagatti/auto-session",
  config = function()
    require("auto-session").setup({
            --  e.g. ~/.local/share/nvim/sessions/
      auto_session_suppress_dirs = { "~/", "~/Projects", "~/Code", "~/Downloads", "/" },
      session_lens = {
        buftypes_to_ignore = {},
        load_on_setup = true,
        theme_conf = { border = true },
        previewer = false,
      },
      vim.keymap.set("n", "<leader>ls", require("auto-session.session-lens").search_session, {
        noremap = true,
      }),
    })
  end,
}
