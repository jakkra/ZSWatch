---
applyTo: "website/**"
---

# ZSWatch Website (zswatch.dev) Development Instructions

## Overview

The `website/` directory contains the [zswatch.dev](https://zswatch.dev) documentation and marketing site, built with **Docusaurus 3.7** (React-based static site generator) and styled with **Tailwind CSS**.

- **URL**: https://zswatch.dev
- **Framework**: Docusaurus 3.7
- **Styling**: Tailwind CSS 3 + custom CSS
- **Node.js**: Use `npm` for package management
- **Deployment**: GitHub Pages (branch `gh-pages`)

## Project Structure

```
website/
├── docusaurus.config.js    # Main site config (URL, navbar, footer, plugins, theme)
├── sidebars.js             # Auto-generated from docs/ folder structure
├── package.json            # Dependencies and scripts
├── tailwind.config.js      # Tailwind CSS configuration
├── postcss.config.js       # PostCSS configuration
├── docs/                   # Documentation pages (Markdown/MDX)
│   ├── intro.md            # Landing doc page
│   ├── getting-started/    # Quickstart, hardware, software setup
│   ├── development/        # Compiling, toolchain, image resources, Linux dev
│   ├── hardware-design/    # PCB design documentation
│   └── hw-testing/         # Hardware testing procedures
├── blog/                   # Blog posts (Markdown)
├── src/
│   ├── components/         # Custom React components
│   │   ├── FirmwareUpdate/ # Web-based BLE firmware update (MCUmgr/SMP)
│   │   ├── GithubNavbar/   # GitHub stars count navbar widget
│   │   ├── HomepageFeatures/ # Landing page feature cards
│   │   └── SubscriptionForm/ # Email subscription form
│   ├── pages/              # Custom pages
│   │   ├── index.js        # Homepage
│   │   └── update.js       # Firmware update page (BLE Web API)
│   ├── theme/              # Docusaurus theme overrides (swizzled components)
│   └── css/                # Custom CSS (Tailwind-based)
└── static/                 # Static assets (images, favicon, social card)
```

## Common Commands

```bash
cd website

# Install dependencies
npm install

# Start development server (hot reload)
npm start

# Production build
npm run build

# Serve production build locally
npm run serve

# Clear Docusaurus cache
npm run clear
```

## Documentation Pages

- Documentation lives in `docs/` as Markdown (`.md`) or MDX (`.mdx`) files
- Sidebar is **auto-generated** from the folder structure (configured in `sidebars.js`)
- Use `_category_.json` files to control folder display name and order
- Front matter supports standard Docusaurus fields (`title`, `sidebar_position`, `description`, etc.)

## Key Configuration

### docusaurus.config.js
- **Site URL**: `https://zswatch.dev`
- **Organization**: `ZSWatch`
- **Color mode**: Dark theme by default, user-switchable
- **Navbar items**: Blog, Docs, FW Update, GitHub stars
- **Analytics**: Google Analytics (gtag)
- **Prism themes**: GitHub (light) / Dracula (dark) for code blocks

### Styling
- Tailwind CSS is configured via `tailwind.config.js` and `postcss.config.js`
- Custom CSS extends the Docusaurus theme in `src/css/custom.css`
- Dark mode is primary; ensure all custom styles work in both themes

## Custom Components

### FirmwareUpdate
Web-based firmware update page using BLE Web API and MCUmgr/SMP protocol. Allows users to flash firmware directly from the browser.

### GithubNavbar
Custom navbar item that displays live GitHub star count for the ZSWatch repository.

### HomepageFeatures
Feature cards displayed on the homepage landing page.

### SubscriptionForm
Email subscription form for project updates.

## Conventions

- **New docs**: Add Markdown files to the appropriate subfolder in `docs/`; the sidebar updates automatically
- **Blog posts**: Add to `blog/` following Docusaurus blog post naming conventions (`YYYY-MM-DD-title.md`)
- **Images**: Place in `static/img/` and reference with `/img/filename.png`
- **React components**: Create in `src/components/` with their own folder containing `index.js` and optional CSS module
- **Environment variables**: Use `.env.local` for local secrets (copy from `.env.example`); access via `customFields` in Docusaurus config
