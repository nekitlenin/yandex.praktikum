<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );

/** MySQL database username */
define( 'DB_USER', 'pyasuko' );

/** MySQL database password */
define( 'DB_PASSWORD', 'mypassword' );

/** MySQL hostname */
define( 'DB_HOST', 'localhost' );

/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         'vPJ#=t-2+0brAz1mC/VCgzCTJXqur]!NHD@^LNdlKvb;_aJw<_u.d)NB5sYtPmW8');
define('SECURE_AUTH_KEY',  ' IavW;iU7--C meOzB+o/Z}#ve-xmlYZG@j+T#cKs~V<t9}@T+-|==B4cT ZFf]T');
define('LOGGED_IN_KEY',    '](g&^<..H4~!]2j84OJ?xyq6}*{l4h)WR~S.e,*CkhsOV|kLPZL,H|v-xy{QuS^u');
define('NONCE_KEY',        'gzBOz!<M5+q!fB`-m`;-%$+Ug7y`,277B[uyP@.ZrU(qdZ)P])WkxZYbZi%?em&+');
define('AUTH_SALT',        'h-f1({;gXU@!m#stmG%+:wuYPaOd8^mvk42wBLbHN@n%lH@}z^c.qO1pE[8xv&Ar');
define('SECURE_AUTH_SALT', '^{+Z$g@dqbm=6DYue-y*-F#69^9C1B-#V|=kw%{`,68 YM9-<n->rwe:(6%w5z;L');
define('LOGGED_IN_SALT',   '?~r]{MYA;WJq#NRe~S6+L.f3A+UQ16Dja2K{f~@wU.i l:I=ZNqjf,Iw-69;VAu}');
define('NONCE_SALT',       'SQ7|_Ft+U+RWO,Mr<H_dH.%W9La^XH$@J,JH/q.6CtMC2lo!Ur)NnXyy#9kK-HC-');

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
        define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
