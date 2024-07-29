local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
  -- bootstrap lazy.nvim
  -- stylua: ignore
  vim.fn.system({ "git", "clone", "--filter=blob:none", "https://github.com/folke/lazy.nvim.git", "--branch=stable", lazypath })
end
vim.opt.rtp:prepend(vim.env.LAZY or lazypath)

require("lazy").setup({
	spec = {
		-- add LazyVim and import its plugins
		{ "LazyVim/LazyVim", import = "lazyvim.plugins" },
		-- import any extras modules here
		-- { import = "lazyvim.plugins.extras.lang.typescript" },
		-- { import = "lazyvim.plugins.extras.lang.json" },
		-- { import = "lazyvim.plugins.extras.ui.mini-animate" },
		-- import/override with your plugins
		{ import = "plugins" },
	},
	defaults = {
		-- By default, only LazyVim plugins will be lazy-loaded. Your custom plugins will load during startup.
		-- If you know what you're doing, you can set this to `true` to have all your custom plugins lazy-loaded by default.
		lazy = false,
		-- It's recommended to leave version=false for now, since a lot the plugin that support versioning,
		-- have outdated releases, which may break your Neovim install.
		version = false, -- always use the latest git commit
		-- version = "*", -- try installing the latest stable version for plugins that support semver
	},
	install = { colorscheme = { "tokyonight", "habamax" } },
	checker = { enabled = true }, -- automatically check for plugin updates
	performance = {
		rtp = {
			-- disable some rtp plugins
			disabled_plugins = {
				"gzip",
				-- "matchit",
				-- "matchparen",
				-- "netrwPlugin",
				"tarPlugin",
				"tohtml",
				"tutor",
				"zipPlugin",
			},
		},
	},
})

require("lspconfig").qmlls.setup({
	cmd = { "/usr/lib/qt6/bin/qmlls" },
	filetypes = { "qml", "qmljs" },
})

require("ts-comments").setup({
    lang = {
     qmljs = "// %s"
    },
})

require("neo-tree").setup({
  filesystem = {
     follow_current_file = {
       enabled = true, -- This will find and focus the file in the active buffer every time
       --              -- the current file is changed while the tree is open.
       leave_dirs_open = false, -- `false` closes auto expanded dirs, such as with `:Neotree reveal`
     },
     window = {
       mappings = {
         ["<leader>p"] = "image_wezterm", -- " or another map
       },
     },
     commands = {
       image_wezterm = function(state)
         local node = state.tree:get_node()
         if node.type == "file" then
           require("image_preview").PreviewImage(node.path)
         end
       end,
     },
   },
 })

