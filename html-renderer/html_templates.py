

css_template = """
<style>
    body {
        font-family: sans-serif;
        padding: 1em;
    }
    h1 {
     text-align: center;
     font-size: 2em;
     margin-bottom: 2em;
    }
    h2 {
        text-align: center;
        font-size: 1.5em;
        margin-top: 2em;
        text-decoration: underline;
    }
     h3 {
        text-align: center;
        font-size: 1.2em;
        margin-top: 2em;
    }
    p {
        font-size: 1.2em;
        text-align: center;
        font-weight: 520;      
    }
    li {
        margin: 0.5em;
        font-size: 1.2em;
        font-weight: 550;
    }
    img {
        width: min(100%, 640px);
        filter: drop-shadow(0px 0px 10px rgba(0, 0, 0, 0.5));
    }
    video {
        width: min(100%, 640px);
        filter: drop-shadow(0px 0px 10px rgba(0, 0, 0, 0.5));
    }
</style>
"""


html_template = """
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>MolSim WS23/24 - Group C</title>
    ###STYLE###
  </head>

  <body style="font-family: sans-serif; padding: 1em">
    <h1>MolSim WS23/24 Submissions - Group C</h1>

    <p>
      This page contains all the submissions for the <b> Molecular Dynamics </b> course at TUM for Group C.
    </p>

    <p>
      The source code for the whole project can be found at
      <a href="https://github.com/ManuelLerchner/MolSim-WS23-24/"> MolSim-WS23-24</a>
      <br/>
      All the data for the submissions can be found in the submissions branch at
      <a href="https://github.com/ManuelLerchner/MolSim-WS23-24/tree/presentations"> MolSim-WS23-24/presentations</a>
    </p>

    <p>
       This page is generated automatically from all the media files in the submissions folder using a <a href="https://github.com/ManuelLerchner/MolSim-WS23-24/tree/presentations/html-renderer"><b>Python</b> script</a> every time a new commit is pushed to the submissions branch.
    </p>

    <h3>Table of Contents</h3>

    ###TABLE_OF_CONTENTS###

    <hr>

    ###CONTENT###
    
  </body>
</html>
"""

content_template = """
<div style="display: flex; flex-direction: column; justify-content: center; align-items: center">
###MEDIA###
<p style="text-align: center; font-size: 1.2em; font-weight: 520;">###SUBTITLE###</p>
</div>
"""

media_wall_template = """
<div style='display: flex; flex-wrap: wrap; justify-content: space-evenly; align-items: center; gap: 1em; margin-top: 2em; margin-bottom: 2em;'>
###MEDIA_WALL###
</div>
"""

toc = """
<div style='display: flex; flex-direction: column; justify-content: center; align-items: center;'>
<ul>
###TOC_ITEMS###
</ul>
</div>
"""
