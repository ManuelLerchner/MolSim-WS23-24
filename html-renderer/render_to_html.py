import os

from html_templates import css_template, html_template, content_template, media_wall_template, toc


def render_content():
    html_content = ""
    toc_items = ""

    files = os.listdir(os.getcwd())

    sheets = list(filter(lambda x: x.startswith("sheet"), files))

    if len(sheets) == 0:
        raise Exception("No sheets found")

    for sheet in sorted(sheets):

        media_wall = ""
        reference_list = ""

        toc_items += "<li><a href='#" + sheet + "'>" + sheet + "</a></li>" + "\n"

        # scan files in submission folder and render them
        for file in sorted(os.listdir(sheet + "/submission")):
            full_path = sheet + "/submission/" + file

            media_id = sheet + "#" + file

            if file.endswith(".png"):
                media = content_template

                media = media.replace(
                    "###MEDIA###", "<img id=" + media_id + " src='" + full_path + "'/>")

                media = media.replace("###MEDIA_ID###", sheet + "#" + file)

                media = media.replace(
                    "###SUBTITLE###", "<a href='#" + media_id + "'>" + file + "</a>")

                media_wall += media
            elif file.endswith(".mp4"):
                media = content_template

                media = media.replace(
                    "###MEDIA###", "<video id=" + media_id+" controls muted><source src='" + full_path + "' type='video/mp4'></video>")

                media = media.replace("###SUBTITLE###", "<a href='#" + media_id + "'>" + file + "</a>")

                media_wall += media
            elif file.endswith(".pdf") or file.endswith(".md"):
                reference_list += "<li><a href='" + full_path+"'>" + file + "</a></li>"

        content = media_wall_template
        content = content.replace("###MEDIA_WALL###", media_wall)

        reference = toc
        reference = reference.replace(
            "###TOC_ITEMS###", reference_list)

        sheet_number = str(int(sheet.split("sheet")[1]))
        section_title = "<h2 id='" + sheet + "'>" + sheet + "</h2>" + "<p><a href='https://github.com/ManuelLerchner/MolSim-WS23-24/releases/tag/Submission-" + \
            sheet_number + "'>Go to GitHub Release " + sheet_number + "</a></p>"

        html_content += section_title + reference + content + "<hr>"

    table_of_contents = toc
    table_of_contents = table_of_contents.replace(
        "###TOC_ITEMS###", toc_items)

    return table_of_contents, html_content


if __name__ == "__main__":
    table_of_contents, content = render_content()

    html_template = html_template.replace("###STYLE###", css_template)

    html_template = html_template.replace(
        "###TABLE_OF_CONTENTS###", table_of_contents)
    html_template = html_template.replace("###CONTENT###", content)

    with open("index.html", "w") as f:
        f.write(html_template)
