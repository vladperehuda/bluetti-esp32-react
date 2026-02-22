import { defineConfig, CommonServerOptions } from 'vite';
import pkg from './package.json';
import checker from 'vite-plugin-checker';
import react from '@vitejs/plugin-react-swc';

const target = process.env.PROXY || pkg.proxy;
const wsTarget = target.replace(/^http(s?):\/\//, "ws$1://");

const devProxyConfig: CommonServerOptions = {
  host: '0.0.0.0',
  open: true,
  port: 3000,
  strictPort: true,
  allowedHosts: true,
  proxy: {
    '/api': {
      target: target,
      xfwd: true,
      changeOrigin: true,
    },
    '/ws': {
      target: wsTarget,
      ws: true,
      changeOrigin: true,
    }
  },
};

export default defineConfig({
  plugins: [
    react(),
    checker({
      typescript: { tsconfigPath: 'tsconfig.json' },
    }),
  ],
  server: devProxyConfig,
  preview: devProxyConfig,
  define: {
    global: 'globalThis',
  },
  esbuild: {
    legalComments: 'none',
  },
  build: {
    chunkSizeWarningLimit: 1024,
    sourcemap: false,
    rollupOptions: {
      output: {
        entryFileNames: 'js/[name].[hash:6].js',
        chunkFileNames: 'js/[name].[hash:6].js',
        assetFileNames: (assetInfo: any) => {
          if (assetInfo.name?.endsWith('.css')) {
            return 'css/[name].[hash:6].css';
          }
          return 'assets/[name].[hash:6][extname]';
        },
      },
    },
  }
});
